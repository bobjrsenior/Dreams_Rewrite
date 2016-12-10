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

        },
        {
            PositionX = 225,
            PositionY = 300,
            IsStatic = false,
            IsCollidable = 1,
            Tag = "Bunny",
            SpritePath = "sprites/GreenStar.png",
            Script = "scripts/ground.lua",
            SpriteStartX = 0,
            SpriteStartY = 0,
            SpriteWidth = 32,
            SpriteHeight = 32

        }
    }
}