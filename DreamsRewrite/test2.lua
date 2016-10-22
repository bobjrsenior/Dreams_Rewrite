function update()
    position = getPosition()
    position["X"] = position["X"] + 0.01
    setPosition(position)
end