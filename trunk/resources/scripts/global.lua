
Log:Instance():LuaWrite("***********************************");
Log:Instance():LuaWrite("*** Iniciando sistema de script ***");
Log:Instance():LuaWrite("***********************************");

Enemy_OnWayPoint = function(id)
	Log:Instance():LuaWrite("El enemigo ha llegado a un WayPoint");
end

Heroe_OnJump = function(id)
	Log:Instance():LuaWrite("El héroe ha saltado");
end

player1_OnCollision = function(id)
	Heroe_OnCollision("player1", id)
end

player2_OnCollision = function(id)
	Heroe_OnCollision("player2", id)
end

Heroe_OnCollision = function(player, id)
	Log:Instance():LuaWrite("El héroe ha chocado con "..id);

	if string.find(id, "Yoshi") ~= nil then
		StateGame:Instance():KillPlayer(player);
	elseif id == "trigger1" then
		StateGame:Instance():SetActiveCamera(0);
	elseif id == "trigger2" then
		StateGame:Instance():SetActiveCamera(1);
	elseif string.find(id, "bola") ~= nil then
		StateGame:Instance():KillObject(player, id);
	end
end