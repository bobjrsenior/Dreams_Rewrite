function update()
    position = getPosition()
    if isKeyDown(KEYCODE["KEY_RIGHT"]) or isKeyDown(KEYCODE["KEY_KEY_D"]) then
        position["X"] = position["X"] + 0.1
        setPosition(position)
    elseif isKeyDown(KEYCODE["KEY_LEFT"]) or isKeyDown(KEYCODE["KEY_KEY_A"]) then
        position["X"] = position["X"] - 0.1
        setPosition(position)
    end
    
    if isKeyDown(KEYCODE["KEY_UP"]) or isKeyDown(KEYCODE["KEY_KEY_W"]) then
        position["Y"] = position["Y"] - 0.1
        setPosition(position)
    elseif isKeyDown(KEYCODE["KEY_DOWN"]) or isKeyDown(KEYCODE["KEY_KEY_S"]) then
        position["Y"] = position["Y"] + 0.1
        setPosition(position)
    end
end