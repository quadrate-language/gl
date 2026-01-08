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

## API

### Initialization

- `LoadGL( -- success:i64)` - Load OpenGL functions via glad (call after context creation)
- `GetVersion( -- major:i64 minor:i64)` - Get OpenGL version

### State Management

- `Enable(cap:i64 -- )` - Enable a capability
- `Disable(cap:i64 -- )` - Disable a capability
- `ClearColor(r:f64 g:f64 b:f64 a:f64 -- )` - Set clear color (RGBA 0.0-1.0)
- `Clear(mask:i64 -- )` - Clear buffers
- `Viewport(x:i64 y:i64 width:i64 height:i64 -- )` - Set viewport

### Buffer Objects

- `GenBuffer( -- buffer:i64)` - Generate a buffer object
- `DeleteBuffer(buffer:i64 -- )` - Delete a buffer object
- `BindBuffer(target:i64 buffer:i64 -- )` - Bind a buffer object
- `BufferDataFloats(target:i64 data:ptr count:i64 usage:i64 -- )` - Upload float data to buffer

### Vertex Arrays

- `GenVertexArray( -- vao:i64)` - Generate a vertex array object
- `DeleteVertexArray(vao:i64 -- )` - Delete a vertex array object
- `BindVertexArray(vao:i64 -- )` - Bind a vertex array object
- `EnableVertexAttribArray(index:i64 -- )` - Enable a vertex attribute array
- `VertexAttribPointer(index:i64 size:i64 type:i64 normalized:i64 stride:i64 offset:i64 -- )` - Define vertex attribute data

### Shaders

- `CreateShader(type:i64 -- shader:i64)` - Create a shader object
- `DeleteShader(shader:i64 -- )` - Delete a shader object
- `ShaderSource(shader:i64 source:str -- )` - Set shader source code
- `CompileShader(shader:i64 -- )` - Compile a shader
- `GetShaderCompileStatus(shader:i64 -- success:i64)` - Check compilation status
- `GetShaderInfoLog(shader:i64 -- log:str)` - Get shader info log

### Programs

- `CreateProgram( -- program:i64)` - Create a program object
- `DeleteProgram(program:i64 -- )` - Delete a program object
- `AttachShader(program:i64 shader:i64 -- )` - Attach a shader to a program
- `LinkProgram(program:i64 -- )` - Link a program
- `GetProgramLinkStatus(program:i64 -- success:i64)` - Check link status
- `GetProgramInfoLog(program:i64 -- log:str)` - Get program info log
- `UseProgram(program:i64 -- )` - Use a program
- `GetUniformLocation(program:i64 name:str -- location:i64)` - Get uniform location
- `Uniform1f(location:i64 v0:f64 -- )` - Set float uniform
- `Uniform1i(location:i64 v0:i64 -- )` - Set integer uniform
- `Uniform3f(location:i64 v0:f64 v1:f64 v2:f64 -- )` - Set vec3 uniform
- `Uniform4f(location:i64 v0:f64 v1:f64 v2:f64 v3:f64 -- )` - Set vec4 uniform

### Drawing

- `DrawArrays(mode:i64 first:i64 count:i64 -- )` - Draw primitives from arrays
- `DrawElements(mode:i64 count:i64 type:i64 offset:i64 -- )` - Draw indexed primitives

### Textures

- `GenTexture( -- texture:i64)` - Generate a texture object
- `DeleteTexture(texture:i64 -- )` - Delete a texture object
- `BindTexture(target:i64 texture:i64 -- )` - Bind a texture object
- `TexParameteri(target:i64 pname:i64 param:i64 -- )` - Set texture parameter
- `ActiveTexture(texture:i64 -- )` - Select active texture unit

## Constants

### Clear Buffer Bits
- `GL_COLOR_BUFFER_BIT`, `GL_DEPTH_BUFFER_BIT`, `GL_STENCIL_BUFFER_BIT`

### Primitive Types
- `GL_POINTS`, `GL_LINES`, `GL_LINE_LOOP`, `GL_LINE_STRIP`
- `GL_TRIANGLES`, `GL_TRIANGLE_STRIP`, `GL_TRIANGLE_FAN`

### Data Types
- `GL_BYTE`, `GL_UNSIGNED_BYTE`, `GL_SHORT`, `GL_UNSIGNED_SHORT`
- `GL_INT`, `GL_UNSIGNED_INT`, `GL_FLOAT`, `GL_DOUBLE`

### Buffer Targets
- `GL_ARRAY_BUFFER`, `GL_ELEMENT_ARRAY_BUFFER`

### Buffer Usage
- `GL_STREAM_DRAW`, `GL_STREAM_READ`, `GL_STREAM_COPY`
- `GL_STATIC_DRAW`, `GL_STATIC_READ`, `GL_STATIC_COPY`
- `GL_DYNAMIC_DRAW`, `GL_DYNAMIC_READ`, `GL_DYNAMIC_COPY`

### Shader Types
- `GL_VERTEX_SHADER`, `GL_FRAGMENT_SHADER`, `GL_GEOMETRY_SHADER`

### Enable/Disable Capabilities
- `GL_BLEND`, `GL_CULL_FACE`, `GL_DEPTH_TEST`
- `GL_SCISSOR_TEST`, `GL_STENCIL_TEST`, `GL_MULTISAMPLE`

### Blend Functions
- `GL_ZERO`, `GL_ONE`, `GL_SRC_COLOR`, `GL_ONE_MINUS_SRC_COLOR`
- `GL_SRC_ALPHA`, `GL_ONE_MINUS_SRC_ALPHA`, `GL_DST_ALPHA`, `GL_ONE_MINUS_DST_ALPHA`
- `GL_DST_COLOR`, `GL_ONE_MINUS_DST_COLOR`

### Texture Targets
- `GL_TEXTURE_1D`, `GL_TEXTURE_2D`, `GL_TEXTURE_3D`, `GL_TEXTURE_CUBE_MAP`

### Texture Parameters
- `GL_TEXTURE_MIN_FILTER`, `GL_TEXTURE_MAG_FILTER`
- `GL_TEXTURE_WRAP_S`, `GL_TEXTURE_WRAP_T`, `GL_TEXTURE_WRAP_R`

### Texture Filter Values
- `GL_NEAREST`, `GL_LINEAR`
- `GL_NEAREST_MIPMAP_NEAREST`, `GL_LINEAR_MIPMAP_NEAREST`
- `GL_NEAREST_MIPMAP_LINEAR`, `GL_LINEAR_MIPMAP_LINEAR`

### Texture Wrap Values
- `GL_REPEAT`, `GL_CLAMP_TO_EDGE`, `GL_MIRRORED_REPEAT`

### Texture Units
- `GL_TEXTURE0` through `GL_TEXTURE7`

### Pixel Formats
- `GL_RED`, `GL_RG`, `GL_RGB`, `GL_RGBA`, `GL_DEPTH_COMPONENT`

### Cull Face Modes
- `GL_FRONT`, `GL_BACK`, `GL_FRONT_AND_BACK`

### Depth Functions
- `GL_NEVER`, `GL_LESS`, `GL_EQUAL`, `GL_LEQUAL`
- `GL_GREATER`, `GL_NOTEQUAL`, `GL_GEQUAL`, `GL_ALWAYS`

### Boolean Values
- `GL_FALSE`, `GL_TRUE`

## Example

See the SDL3 bindings repository for a complete OpenGL example using SDL3 for window/context creation.

## License

Apache-2.0
