# Contributing to Trilib

Thank you for your interest in contributing to Trilib! We welcome contributions of all kinds, including bug reports, feature suggestions, documentation improvements, and code contributions.

## Getting Started

1. Fork the repository on GitHub
2. Clone your fork locally:
   ```bash
   git clone https://github.com/yourusername/Trilib.git
   cd Trilib
   ```
3. Create a new branch for your work:
   ```bash
   git checkout -b feature/your-feature-name
   ```

## Development Guidelines

### Code Style

- Use consistent indentation (spaces or tabs - please match existing style)
- Keep lines reasonably short for readability
- Use meaningful variable and function names
- Add comments for complex logic

### Header-Only Library Requirements

Since Trilib is a header-only library:
- All implementations must be in `.hpp` files
- Use `inline` for function definitions where appropriate
- Ensure template instantiation works with all supported types (int, float, double)
- Test with different numeric types

### Testing

Before submitting a pull request:
- Compile with C++17 or later
- Test with at least two different numeric types (e.g., float and double)
- Verify no compiler warnings are generated
- Ensure backward compatibility

### Documentation

- Update the README.md if adding or modifying APIs
- Include clear function documentation in header comments
- Provide examples for new features in the README or examples directory
- Update API Reference section with new functions

## Submitting Changes

### Pull Request Process

1. Ensure all changes are committed to your feature branch
2. Push to your fork: `git push origin feature/your-feature-name`
3. Create a Pull Request on GitHub with:
   - Clear title describing the changes
   - Description of what the PR accomplishes
   - Any relevant issue numbers (e.g., "Fixes #123")
   - Information about testing performed

### Commit Messages

Write clear, descriptive commit messages:
- Use imperative mood ("Add feature" not "Added feature")
- Keep the first line under 50 characters
- Provide detailed explanation in the body if needed
- Reference issue numbers when applicable

Example:
```
Add circumcenter calculation for triangles

Implements the circumcenter() function that calculates the center
of the circle passing through all three vertices of a triangle.
Uses the standard geometric formula for circumcenter computation.

Fixes #42
```

## Reporting Issues

When reporting bugs:
- Check existing issues first to avoid duplicates
- Provide a clear, descriptive title
- Include minimal code example to reproduce the issue
- Specify your compiler version and C++ standard used
- Include expected vs. actual behavior

## Feature Requests

To suggest a new feature:
- Explain the use case
- Provide examples of how it would be used
- Discuss any potential performance implications
- Consider whether it fits the scope of a triangle/vector math library

## Questions?

- Open an issue with the `question` label
- Provide context and details about what you're trying to understand

## Code of Conduct

We are committed to providing a welcoming and inclusive environment. Be respectful and constructive in all interactions.

## License

By contributing to Trilib, you agree that your contributions will be licensed under the MIT License.

Thank you for contributing!
