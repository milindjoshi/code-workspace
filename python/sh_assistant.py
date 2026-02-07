import ollama
import subprocess
import re
import os
import readline
import shlex

# Setup history
HISTFILE = os.path.expanduser("~/.ai_assistant_history")
try:
    readline.read_history_file(HISTFILE)
except FileNotFoundError:
    pass

import atexit
atexit.register(readline.write_history_file, HISTFILE)

def clean_command(text):
    """Deep cleans AI output to get only the raw shell command."""
    # Remove markdown code blocks
    text = re.sub(r'```[a-z]*', '', text)
    text = text.replace('```', '')
    # Remove single backticks
    text = text.replace('`', '')
    # Split by newline and take ONLY the first line as the command
    first_line = text.strip().split('\n')[0]
    return first_line.strip()

def run_sh_assistant():
    BLUE, GREEN, YELLOW, RESET = "\033[1;34m", "\033[1;32m", "\033[1;33m", "\033[0m"

    print(f"{BLUE}--- ⌨️ AI Shell Assistant (Stable Version) ---{RESET}")
    
    system_rules = (
        "You are a Linux command generator. Output ONLY the command on the first line. "
        "Explanation on the second line. No markdown. No backticks. "
        "Use absolute paths or ~/ correctly."
    )

    while True:
        try:
            user_req = input(f"{BLUE}Prompt:{RESET} ")
        except EOFError: break
        
        if user_req.lower() in ['exit', 'quit']: break
        if not user_req.strip(): continue

        try:
            response = ollama.chat(model='fast-phi', messages=[
                {'role': 'system', 'content': system_rules},
                {'role': 'user', 'content': user_req}
            ])
            
            raw_content = response['message']['content'].strip()
            cmd = clean_command(raw_content)
            
            # Extract explanation (everything after the first line)
            parts = raw_content.split('\n')
            explanation = "\n".join(parts[1:]).strip() if len(parts) > 1 else ""

            print(f"\n💡 {GREEN}Command:{RESET} {cmd}")
            if explanation: print(f"📖 {explanation}")

            confirm = input(f"\n{YELLOW}Execute? (y/N): {RESET}").lower()
            if confirm == 'y':
                # os.path.expanduser handles the ~/ issue properly
                full_cmd = os.path.expanduser(cmd)
                print(f"Running: {full_cmd}...\n")
                
                # Using a 15-second timeout via subprocess argument instead of shell 'timeout' command
                # This is more stable in Python
                subprocess.run(full_cmd, shell=True, executable='/bin/zsh', timeout=15)
                
                print(f"\n{BLUE}{'-'*30}{RESET}")
        except subprocess.TimeoutExpired:
            print(f"\n{YELLOW}⚠️ Command timed out after 15 seconds.{RESET}")
        except Exception as e:
            print(f"\n❌ Error: {e}")

if __name__ == "__main__":
    run_sh_assistant()
