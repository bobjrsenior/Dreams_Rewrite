function update()
    if isKeyDown(KEYCODE["KEY_ESCAPE"]) then
        forceKeyUp(KEYCODE["KEY_RETURN"])
        quitGame()
    end
    
    if isKeyDown(KEYCODE["KEY_RETURN"]) then
        forceKeyUp(KEYCODE["KEY_RETURN"])
        loadScene(1)
        return
    end
    
    screenWidth = getScreenWidth()
    screenHeight = getScreenHeight()    

    if isKeyDown(KEYCODE["KEY_DOWN"]) then
        position = {X = screenWidth / 2, Y = 3 * screenHeight / 4}
        setPosition(position)
        playSound("sfx\\down.wav")
    else
        position = {X = screenWidth * 2, Y = 0}
        setPosition(position)
    end
end