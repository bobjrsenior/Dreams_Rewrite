# Config File Specifications

## Config.lua

Must always be named Config.lua.

This is the main config file for the game and is required.

    Config = {
        Title = "Test Window Title",
        Fullscreen = 0,
        ScreenWidth = 640,
        ScreenHeight = 480,
        Scenes = {
            "scenes/scene1.lua",
        },
        AssetFolder = "Assets/"
    }
    
* Title: The game windows title (string)
* Fullscreen: 0 if the game is windowed. 1 if the game should be fullscreen
* ScreenWidth: The width of the game window in pixels (whole number)
* ScreenHeight: The height of the game window in pixels (whole number)
* Scenes: A lua table with paths to scene configs files as entries (each entry is a string)
* AssetFolder: Path the the games main asset folder ("Assets/" by default) (string)

## Scene

Required for each scene in the game.
 
    Scene = {
        GameObjects = {
            {
                PositionX = 75,
                PositionY = 75,
                IsStatic = false,
                IsCollidable = 1,
                Tag = "Player",
                SpritePath = "sprites/RedSquare.png",
                Script = "scripts/player.lua",
                SpriteStartX = 0,
                SpriteStartY = 0,
                SpriteWidth = 32,
                SpriteHeight = 32
            }
        }
    }
    
* GameObjects: A lua table containing a GameObject for each entry

## GameObject

Objects in the game

    {
        PositionX = 75,
        PositionY = 75,
        IsStatic = false,
        IsCollidable = 1,
        Tag = "Player",
        SpritePath = "sprites/RedSquare.png",
        Script = "scripts/player.lua",
        SpriteStartX = 0,
        SpriteStartY = 0,
        SpriteWidth = 32,
        SpriteHeight = 32
    }

* PositionX: The initial X position of this object
* PositionY: The initial Y position of this object
* IsStatic: Does this object move? (currently a placeholder parameter)
* IsCollidable: Does this object collide with others (1 = does collide, 0 = doesn't collide)?
* Tag: A tag that identifies this type of object (string)
* SpritePath: The location of this objects sprite
* Script: The location of this objects script (containing an update function)
* SpriteStartX: What X pixel the sprite starts at in the Sprite image
* SpriteStartY: What Y pixel the sprite starts at in the Sprite image
* SpriteWidth: The width of the sprite in pixels
* SpriteHeight: The height of the sprite in pixels