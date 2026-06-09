import streamlit as st
import serial
import time
import pandas as pd
from datetime import datetime

# Configure web page layout
st.set_page_config(page_title="Door Automation Dashboard", layout="wide")

# --- Initialize Serial Connection ---
@st.cache_resource
def init_serial():
    # Replace 'COM3' with your specific Arduino port
    return serial.Serial('COM3', 9600, timeout=0.05)

try:
    ser = init_serial()
except Exception as e:
    st.error(f"⚠️ Could not connect to Serial Port: {e}")
    ser = None

# --- Initialize Persistent Session State ---
if "logs" not in st.session_state:
    st.session_state.logs = []
if "current_state" not in st.session_state:
    st.session_state.current_state = "Unknown"
if "current_dist" not in st.session_state:
    st.session_state.current_dist = "0"

st.title("🚪 Automatic Door Control & Logistics")
st.markdown("---")

# Main Page Layout Split
col1, col2 = st.columns(2)

# COLUMN 1: The Static Control Panel (Will NEVER flicker now)
with col1:
    st.subheader("⚙️ Settings")
    threshold_val = st.number_input(
        "Enter Distance Threshold (cm)", 
        min_value=5, 
        max_value=300, 
        value=50, 
        step=5
    )
    
    if st.button("Submit New Threshold", use_container_width=True):
        if ser and ser.is_open:
            command = f"SET_THRESHOLD,{threshold_val}\n"
            ser.write(command.encode('utf-8'))
            
            now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            st.session_state.logs.insert(0, [now, "COMMAND SENT", f"Threshold updated to {threshold_val} cm"])
            st.success(f"Sent: SET_THRESHOLD,{threshold_val}")
        else:
            st.error("Serial connection is offline.")

# COLUMN 2: Live Data & Logs (Wrapped inside a seamless auto-refresh fragment)
with col2:
    st.subheader("📊 Live Tracking")
    
    # We set this specific container to auto-refresh every 0.5 seconds in the background
    @st.fragment(run_every=0.5)
    def live_updates_pool():
        # 1. Read Serial Data packet if available
        if ser and ser.is_open and ser.in_waiting > 0:
            try:
                line = ser.readline().decode('utf-8').strip()
                if line and "," in line:
                    state_code, distance = line.split(',')
                    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                    door_text = "🔓 OPEN" if state_code == "1" else "🔒 CLOSED"
                    
                    # Track changes for the log file
                    if door_text != st.session_state.current_state:
                        st.session_state.logs.insert(0, [timestamp, "DOOR STATE CHANGE", f"Door became {door_text}"])
                        st.session_state.current_state = door_text
                    
                    st.session_state.current_dist = distance
            except Exception:
                pass # Handle data clipping gracefully

        # 2. Render Metrics smoothly inside the fragment
        m_col1, m_col2 = st.columns(2)
        m_col1.metric("Door State", st.session_state.current_state)
        m_col2.metric("Object Distance", f"{st.session_state.current_dist} cm")
        
        st.markdown("---")
        st.subheader("📜 System Logs")
        
        # 3. Render Table smoothly
        if st.session_state.logs:
            df = pd.DataFrame(st.session_state.logs, columns=["Time", "Event Type", "Details"])
            st.dataframe(df, use_container_width=True, hide_index=True)
        else:
            st.info("Awaiting data from Arduino...")

    # Execute the fragment
    live_updates_pool()