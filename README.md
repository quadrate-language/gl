# gl

OpenGL bindings for Quadrate using the glad loader.

## Installation

```bash
quadpm get https://github.com/quadrate-language/gl
```

## Requirements

- OpenGL development libraries
- An OpenGL context (typically created via SDL3 or similar)

## Usage

```qd
use gl

fn main() {
    // After creating an OpenGL context, load GL functions
    gl::LoadGL drop

    // Set clear color to cornflower blue
    0.39 0.58 0.93 1.0 gl::ClearColor

    // Clear the screen
    gl::GL_COLOR_BUFFER_BIT gl::Clear
}
```

## Example

See the SDL3 bindings repository for a complete OpenGL example using SDL3 for window/context creation.

## License

Apache-2.0
