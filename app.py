import streamlit as st
import subprocess
import re

def validate_input(user_input):
    if not user_input.strip():
        return "Input cannot be empty."
    if user_input.isnumeric():
        return "Input cannot be purely numerical."
    if not any(c.isupper() for c in user_input):
        return "Input must contain at least one capital letter."
    return None

def run_molecule_expansion(input_str):
    try:
        result = subprocess.run(['./moleculeExpansion', input_str], capture_output=True, text=True, check=True)
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        return f"Error: {e.stderr.strip()}"

# Streamlit UI
st.title("Molecule Expansion")
st.markdown("Enter a molecular formula to expand")

# Input Box (Centered using CSS)
st.markdown("<style>.stTextInput { text-align: center; }</style>", unsafe_allow_html=True)
user_input = st.text_input("Enter a compound:", "", key="compound_input")

# Run Button
if st.button("Run Expansion"):
    error_message = validate_input(user_input)
    if error_message:
        st.error(error_message)
    else:
        output = run_molecule_expansion(user_input)
        st.text_area("Result:", output, height=100)
