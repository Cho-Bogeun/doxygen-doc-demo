# Doxygen documentation demo

A small C++ example that uses Doxygen as both an API reference generator and a lightweight design-document system.

## What this demonstrates

- Short API contracts close to the C++ declarations
- A standalone `.dox` design page for longer explanations
- Mermaid diagrams kept in external `.mmd` files
- Reusable LaTeX formula macros kept in `formulas.tex`
- Markdown tables inside Doxygen pages
- Cross-links between design pages and C++ symbols
- GitHub Actions build with a pinned Doxygen version

## Repository layout

```text
.
├── .github/
│   └── workflows/
│       └── docs.yml
├── docs/
│   ├── diagrams/
│   │   └── tracking.mmd
│   ├── formulas.tex
│   └── tracking.dox
├── include/
│   └── tracking.hpp
├── .gitignore
├── Doxyfile
└── README.md
```

## Build locally

Doxygen 1.17 or newer is required for native Mermaid support.

```bash
doxygen Doxyfile
```

Then open:

```text
build/docs/html/index.html
```

The GitHub Actions workflow pins Doxygen 1.18.0 and verifies the official SHA-256 checksum before installing it.

## GitHub Pages

Normal pushes build the documentation and upload the generated HTML as an Actions artifact.

To publish it with GitHub Pages:

1. Open **Settings → Pages**.
2. Set **Source** to **GitHub Actions**.
3. Open the **Doxygen docs** workflow.
4. Run it manually with **Run workflow**.

Manual runs build the same documentation and then deploy it to GitHub Pages.

## Where to look first

Start with:

- `docs/tracking.dox` — the long-form design page
- `include/tracking.hpp` — the corresponding C++ API contracts
- `docs/diagrams/tracking.mmd` — external Mermaid source
- `docs/formulas.tex` — reusable formula macros
