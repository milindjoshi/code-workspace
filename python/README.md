🤖 Local AI Workspace
A collection of high-performance Python utilities leveraging Local SLMs (Small Language Models) and Ollama to automate developer workflows and document intelligence.

🌟 Overview
This workspace is designed to bring the power of LLMs directly to the local terminal, ensuring data privacy and reducing API costs by using models like Qwen2.5-coder and Llama3.

🛠️ The Toolkit
1. 📂 GDrive RAG Analyzer (gdrive_rag.py)
Purpose: Semantic search and Q&A across cloud-hosted documents.

Key Tech: rclone VFS integration, JSON indexing, Retrieval-Augmented Generation (RAG).

Use Case: Instantly query SOWs or project docs in Google Drive without manual reading.

2. 📄 Document Intelligence (doc_analyzer.py)
Purpose: Deep analysis and summarization of specific .docx and .txt files.

Key Tech: python-docx parsing, Prompt Engineering.

Use Case: Extracting legal clauses or action items from long reports.

3. 💻 Code Reviewer (code_review.py)
Purpose: Automated static analysis and logic verification.

Key Tech: Zero-shot prompting for bug detection.

Use Case: Identifying security flaws or refactoring opportunities before a commit.

4. 🐚 Shell Assistant (sh_assistant.py)
Purpose: Natural language to Bash/Zsh command conversion.

Key Tech: Context-aware CLI generation.

Use Case: Rapidly generating complex find, sed, or awk commands.

5. 💬 General Chat (chat.py)
Purpose: A lightweight, persistent terminal interface for general LLM interaction.

🚀 Getting Started
Environment Setup:

Bash
python3 -m venv aienv
source aienv/bin/activate
pip install -r requirements.txt
Configuration:
Rename .env.example to .env and configure your local paths and model preferences.

Requirements:

Ollama

Rclone (for GDrive integration)
