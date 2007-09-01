
Log:Instance():LuaWrite("***********************************");
Log:Instance():LuaWrite("*** Iniciando sistema de script ***");
Log:Instance():LuaWrite("***********************************");

Enemy_OnWayPoint = function()
	Log:Instance():LuaWrite("El enemigo ha llegado a un WayPoint");
end

Heroe_OnJump = function()
	Log:Instance():LuaWrite("El héroe ha saltado");
end

Heroe_OnCollision = function()
	Log:Instance():LuaWrite("El héroe ha chocado con un enemigo");
	StateGame:Instance():KillPlayer();
end