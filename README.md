# 🔍 RepoInsight: Agentic Graph-RAG for C++ Analysis

**RepoInsight** is a sophisticated AI-native static analysis tool designed to navigate and explain complex C++ codebases. Unlike standard RAG systems, RepoInsight combines **Semantic Vector Search** with a **Structural Knowledge Graph** to trace deep dependencies and architectural patterns autonomously.

---

## 🏗️ System Architecture

RepoInsight uses a decoupled architecture to separate ingestion, reasoning, and the interface layer.

```mermaid
graph TD
    A[C++ Repository] -->|Tree-Sitter| B(AST Parsing)
    B --> C{Knowledge Ingestion}
    C -->|Structural| D[NetworkX Graph .gml]
    C -->|Semantic| E[ChromaDB Vector Store]
    F[User Query] --> G[FastAPI Backend]
    G --> H[LangGraph Agent]
    H -->|Trace Call Chains| D
    H -->|Semantic Search| E
    H -->|Reasoning| I[Principal Engineer LLM]
    I --> J[Architectural Insights]
