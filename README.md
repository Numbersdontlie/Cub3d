# Cub3D - A Ray Casting FPS Engine

## 🎮 Features
- **Ray Casting Engine** - 1992-style FPS rendering
- **Textured Walls** - North, South, East, West textures
- **Minimap** (bonus) - Real-time player position tracking
- **Smooth Movement** - WASD + mouse rotation
- **Collision Detection** - Walls and boundaries

## 🚀 Quick Start
\`\`\`bash
make
./cub3D maps/map.cub
\`\`\`

## 🎯 Performance
- **FPS:** ~60 on standard hardware
- **Resolution:** 640x480 (configurable)
- **Texture Size:** 64x64 pixels

## 🛠️ Technologies
- **Graphics:** MinilibX (X11)
- **Language:** C
- **Build System:** Make

## 📊 Project Statistics
- **Lines of Code:** ~3000
- **Source Files:** 20+
- **Bonus Features:** Minimap, Door mechanics

## 🎮 Controls
| Key | Action |
|-----|--------|
| W | Move Forward |
| S | Move Backward |
| A | Move Left |
| D | Move Right |
| ← → | Rotate View |
| ESC | Exit |

## 📁 Map Format (.cub)
\`\`\`
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
WE ./path/to/west_texture.xpm
EA ./path/to/east_texture.xpm
F 220,100,0
C 225,30,0

111111
100001
101N01
111111
\`\`\`


