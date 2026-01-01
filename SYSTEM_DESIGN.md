System Design: RepoInsight Graph-RAG Agent

1. Problem Statement
Understanding large-scale C++ repositories is challenging due to:

Implicit Dependencies: Header includes and cross-file function calls.
Semantic Gaps: Searching for "how does the player work" is difficult with standard grep/find.
Architectural Complexity: Manual call-chain tracing is time-consuming and prone to error.

Why this matters?
While standard RAG systems struggle with the non-linear nature of C++ (headers, circular dependencies, and inheritance), RepoInsight utilizes 
a Knowledge Graph to provide the LLM with a structural 'map,' enabling it to perform multi-file traces that are impossible with vector search alone.

2. High-Level Architecture
The system follows a Decoupled Microservice Architecture consisting of three primary layers:

A. The Ingestion Pipeline (ETL)
Parser: Uses tree-sitter to generate an Abstract Syntax Tree (AST).

Vector Store: Code snippets are embedded and stored in ChromaDB for semantic retrieval.

Knowledge Graph: Structural relationships (classes, functions, includes) are mapped into a NetworkX directed graph (GML format).

B. The Agentic Core (LangGraph)
The "Brain" of the system is a stateful agent that uses a Cycle-based reasoning loop:

Plan: The LLM analyzes the user query.

Act: The agent selects between code_search_tool (Vector DB) or dependency_trace_tool (Graph DB).

Observe: The agent evaluates the tool output.

Repeat/Finalize: The agent continues until the architectural path is fully traced.

C. The Interface Layer (FastAPI)
Endpoint: POST /analyze

Schema: Pydantic models for strict input validation.

Documentation: Integrated Swagger/OpenAPI for developer self-service.

3. Key Technical Decisions
Why Graph-RAG? Standard RAG fails to understand "context" across files. By combining a Graph (structure) with a Vector DB (meaning), the agent can "hop" from a function call in main.cpp to its definition in playlist.h.

Memory Safety Focus: The system prompt is tuned to prioritize C++ memory safety (identifying raw pointers, malloc, and manual memory management).

Portability: Containerized via Docker to ensure environmental consistency across development and production.

4. Scalability & Future Improvements
Hybrid Search: Implementation of Reciprocal Rank Fusion (RRF).

Azure OpenAI Integration: Moving from OpenRouter to enterprise-grade inference.

Persistence: Moving from a local GML file to a graph database like Neo4j for larger repositories.
