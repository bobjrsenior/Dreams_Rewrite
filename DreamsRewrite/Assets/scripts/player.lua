velocity = {X = 0, Y = 0}
playerPosition = {X = 0, Y = 0}
playerDelta = {X = 0, Y = 0}
playerInit = 0
canJump = 1

function update()
    if isKeyDown(KEYCODE["KEY_ESCAPE"]) then
        quitGame()
        return
    end
    
    if isKeyDown(KEYCODE["KEY_RETURN"]) then
        forceKeyUp(KEYCODE["KEY_RETURN"])
        loadScene(getSceneIndex() + 1)
        return
    end
    
    screenWidth = getScreenWidth()
    screenHeight = getScreenHeight()

    xRatio = screenWidth / 640.0
    yRatio = screenHeight / 480.0
    
    xLock = 0
    yLock = 0

    position = {X = 0, Y = 0}
    
    if playerInit == 0 then
        position = getPosition()
        playerPosition = position
        playerPosition["X"] = position["X"]
        playerPosition["Y"] = position["Y"]
        playerInit = 1
    else
        position["X"] = playerPosition["X"]
        position["Y"] = playerPosition["Y"]
    end
    
    deltaTime = getDeltaTime()
    collision = isColliding()
    if tableLength(collision) > 0 then
        for _,value in ipairs(collision) do
            if compareTag(value, "Goal") == 1 then
                loadScene(getSceneIndex() + 1)
            elseif compareTag(value, "Enemy") == 1 then
                loadScene(getSceneIndex())
            else
                collisionDir = collisionDirection(value)
                if math.abs(collisionDir["X"]) > math.abs(collisionDir["Y"]) then
                    if collisionDir["X"] > 0 then
                        xLock = 1
                    else
                        xLock = -1
                    end
                else
                    if collisionDir["Y"] > 0 then
                        yLock = 1
                        canJump = 1
                        if velocity["Y"] > 0 then
                            velocity["Y"] = 0
                        end
                    else
                        yLock = -1
                        if velocity["Y"] < 0 then
                            velocity["Y"] = 0
                        end
                    end
                end
            end
        end
    end

    
    if xLock ~= 1 and (isKeyDown(KEYCODE["KEY_RIGHT"]) or isKeyDown(KEYCODE["KEY_KEY_D"])) then
        position["X"] = position["X"] + xRatio
    elseif xLock ~= -1 and (isKeyDown(KEYCODE["KEY_LEFT"]) or isKeyDown(KEYCODE["KEY_KEY_A"])) then
        position["X"] = position["X"] - xRatio
    end
    
    if yLock ~= -1 and canJump == 1  and (isKeyDown(KEYCODE["KEY_UP"]) or isKeyDown(KEYCODE["KEY_KEY_W"])) then
        velocity["Y"] = velocity["Y"] - 5
        canJump = 0
    end
    
    if yLock ~= 1 then
        velocity["Y"] = velocity["Y"] + (0.01 * deltaTime)

    end

    position["Y"] = position["Y"] + (velocity["Y"] * yRatio)

        
    if position["Y"] >= screenHeight - 16 then
        position["Y"] = screenHeight - 16
        velocity["Y"] = 0
        canJump = 1
    end
    
    playerDelta["X"] = position["X"] - playerPosition["X"]
    playerDelta["Y"] = position["Y"] - playerPosition["Y"]
    playerPosition = position
    
    realPosition = getPosition()
    realPosition["Y"] = playerPosition["Y"]
    setPosition(realPosition)
end