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
            PositionX = 420,
            PositionY = 480-64,
            IsStatic = false,
            IsCollidable = 1,
            Tag = "Enemy",
            SpritePath = "sprites/Enemy.png",
            Script = "scripts/enemyMovement.lua",
            SpriteStartX = 0,
            SpriteStartY = 0,
            SpriteWidth = 32,
            SpriteHeight = 32

        },
        {
            PositionX = 360,
            PositionY = 480-64,
            IsStatic = false,
            IsCollidable = 1,
            Tag = "Goal",
            SpritePath = "sprites/Goal.png",
            Script = "scripts/ground.lua",
            SpriteStartX = 0,
            SpriteStartY = 0,
            SpriteWidth = 32,
            SpriteHeight = 32

        },
        {
            PositionX = 420,
            PositionY = -500,
            IsStatic = false,
            IsCollidable = 1,
            Tag = "livesUI",
            SpritePath = "sprites/Enemy.png",
            Script = "scripts/lives.lua",
            SpriteStartX = 0,
            SpriteStartY = 0,
            SpriteWidth = 32,
            SpriteHeight = 32

        }
    }
}