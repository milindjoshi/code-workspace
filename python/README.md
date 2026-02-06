# 🤖 Local AI Workspace

Custom Python tools for interacting with Small Language Models (SLMs) locally. This setup is optimized for CPU-only execution within an Ubuntu Virtual Machine using Ollama.

## 🛠️ Included Tools

### 1. Interactive AI Chat (`chat.py`)
A real-time, streaming terminal interface for conversation with local models.
- **Optimized Performance:** Uses `fast-phi` (a custom-tuned Phi-3) for faster response times.
- **Streaming UI:** Implements token-by-token text generation so you see the AI "thinking" in real-time.

### 2. Multi-Model Code Reviewer (`code_review.py`)
A specialized tool for analyzing source code from the `~/code-workspace/java` and `~/code-workspace/cpp` directories.
- **Dual Model Support:** Can be toggled between `fast-phi` (general logic) and `qwen2.5-coder` (deep programming analysis).
- **Features:** Automated bug detection, logic summarization, and performance optimization tips.

## 🏗️ Local Model Configuration

The following models are used in this workspace:
* **fast-phi**: A customized version of Microsoft's Phi-3 with a reduced context window (`num_ctx 2048`) to prevent VM RAM stalls.
* **qwen2.5-coder**: A state-of-the-art SLM trained specifically for code generation and review.

## 🚀 Quick Start

1. **Activate Environment:**
   ```zsh
   source aienv/bin/activate
