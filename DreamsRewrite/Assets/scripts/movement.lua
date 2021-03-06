function update()
    if isKeyDown(KEYCODE["KEY_ESCAPE"]) then
        quitGame()
    end
    
    if isKeyDown(KEYCODE["KEY_RETURN"]) then
        forceKeyUp(KEYCODE["KEY_RETURN"])
        loadScene(1)
        return
    end
    
    screenWidth = getScreenWidth()
    screenHeight = getScreenHeight()
    change = 0

    position = getPosition()
    
    
    if position["X"] < screenWidth and (isKeyDown(KEYCODE["KEY_RIGHT"]) or isKeyDown(KEYCODE["KEY_KEY_D"])) then
        position["X"] = position["X"] + (1 * (screenWidth / 640))
        change = 1
    elseif position["X"] > 0 and (isKeyDown(KEYCODE["KEY_LEFT"]) or isKeyDown(KEYCODE["KEY_KEY_A"])) then
        position["X"] = position["X"] - (1 * (screenWidth / 640))
        change = 1
    end
    
    if position["Y"] > 0 and (isKeyDown(KEYCODE["KEY_UP"]) or isKeyDown(KEYCODE["KEY_KEY_W"])) then
        position["Y"] = position["Y"] - (1 * (screenHeight / 640))
        change = 1
    elseif position["Y"] < screenHeight and (isKeyDown(KEYCODE["KEY_DOWN"]) or isKeyDown(KEYCODE["KEY_KEY_S"])) then
        position["Y"] = position["Y"] + (1 * (screenHeight / 640))
        change = 1
    end
    
    if change == 1 then
        setPosition(position)
    end
end