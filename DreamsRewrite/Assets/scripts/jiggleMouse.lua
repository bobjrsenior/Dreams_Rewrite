last = 0

function update()
    if isKeyDown(KEYCODE["KEY_ESCAPE"]) then
        quitGame()
        return
    end
    if isKeyDown(KEYCODE["KEY_RETURN"]) then
        forceKeyUp(KEYCODE["KEY_RETURN"])
        loadScene(3)
        return
    end
    

    curTime = getTime()
    if curTime - last > 3000 then
        last = curTime
        mousePos = getMousePos()
        mousePos["X"] = curTime % getScreenWidth()
        mousePos["Y"] = (curTime * curTime) % getScreenHeight()
        setMousePos(mousePos)
        
        setClearColor(curTime % 255, (curTime * curTime) % 255, (curTime % 127) + (curTime * curTime) % 128, 255)
        
    end
end