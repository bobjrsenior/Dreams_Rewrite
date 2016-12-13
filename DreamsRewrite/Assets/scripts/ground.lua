function update()
    position = getPosition()
    
    position["X"] = position["X"] - playerDelta["X"]
    
    setPosition(position)
end