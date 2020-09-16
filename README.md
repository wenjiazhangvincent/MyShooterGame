## Find more details in https://github.com/wenjiazhangvincent/MyShooterGame

# DONE LIST

## ID Allocator
Allocate runtime ID for each system.

## Global Context
Provide convenient for cross-system (cross-file) access.

## Design Table System
Load level/object infomation by reading (.csv) files.
 
## Level System
Manage all level units (such as position, random unit's generating chance).

## Object System
Manage all ships, bullets and other objects.
I seperate object's attributes into level system and Object system because an object shouldn't know it's position or generating change before it's appearance.

## Tick System
Manage all system's tick function.
Game pause function will be easy implemented in this system.

## Render System
Manage all images and fonts which need to be rendered;
Images are stored in Object system. && Fonts are stored in Render system.

## Input System
Seperate key code's button states to Pressed/Presssing/Released by Simple2D's functions(isKeyPressed()/isKeyReleased()).


# TODO LIST

## Colliding System
## Damage System
## Different bullets (such as lazer, tracing bulltes)
## Score