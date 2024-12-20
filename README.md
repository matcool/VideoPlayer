# VideoPlayer

Provides an API for playing mpeg (.mpg) videos within the Geode SDK

## Usage

```cpp
#include <fig.video_player/include/VideoPlayer.hpp>

auto* node = videoplayer::VideoPlayer::create(Mod::get()->getResourcesDir() / "video.mpg");
addChild(node);
```