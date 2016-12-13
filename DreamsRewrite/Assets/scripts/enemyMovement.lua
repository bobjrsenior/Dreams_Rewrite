velocity2 = {X = 0, Y = 0}
canJump2 = 1
direction = 1

function update()
    
    screenWidth = getScreenWidth()
    screenHeight = getScreenHeight()

    xRatio = screenWidth / 640.0
    yRatio = screenHeight / 480.0
    
    xLock = 0
    yLock = 0

    position = getPosition()
    
    position["X"] = position["X"] - playerDelta["X"]
    
    deltaTime = getDeltaTime()
    collision = isColliding()
    if tableLength(collision) > 0 then
        for _,value in ipairs(collision) do
            if compareTag(value, "Goal") == 1 then
                
            elseif compareTag(value, "Enemy") == 1 then

            elseif compareTag(value, "Player") == 1 then

            else
                collisionDir = collisionDirection(value)
                if math.abs(collisionDir["X"]) > math.abs(collisionDir["Y"]) then
                    if collisionDir["X"] > 0 then
                        xLock = 1
                        direction = -xLock
                    else
                        xLock = -1
                        direction = -xLock
                    end
                else
                    if collisionDir["Y"] > 0 then
                        yLock = 1
                        canJump2 = 1
                        if velocity2["Y"] > 0 then
                            velocity2["Y"] = 0
                        end
                    else
                        yLock = -1
                        if velocity2["Y"] < 0 then
                            velocity2["Y"] = 0
                        end
                    end
                end
            end
        end
    end

    
    if position["X"] >= screenWidth - 16 then
        direction = -1
    elseif position["X"] <= 0 then
        direction = 1
    end
    
    if xLock ~= 1 and position["X"] < screenWidth + 16 and direction == 1 then
        position["X"] = position["X"] + (1.5 * xRatio)
    elseif xLock ~= -1 and position["X"] > 0 and direction == -1 then
        position["X"] = position["X"] - (1.5 * xRatio)
    end
    
    --[[
    if yLock ~= -1 and canJump2 == 1  and (isKeyDown(KEYCODE["KEY_UP"]) or isKeyDown(KEYCODE["KEY_KEY_W"])) then
        velocity2["Y"] = velocity2["Y"] - 5
        canJump2 = 0
    end
    --]]
    
    if yLock ~= 1 then
        velocity2["Y"] = velocity2["Y"] + (0.01 * deltaTime)

    end

    position["Y"] = position["Y"] + (velocity2["Y"] * yRatio)

        
    if position["Y"] >= screenHeight - 16 then
        position["Y"] = screenHeight - 16
        velocity2["Y"] = 0
        canJump2 = 1
    end
    
    setPosition(position)
end