if (!session || !session.authenticated)
{
	logger.error("No session or session not authenticated.");
	response.setStatus(401);
	response.send();
	return;
}

var memory = {
    stats: system.exec(system.osName == "Darwin" ? "memory_pressure" : "free")
};

response.contentType = 'application/json';
response.write(JSON.stringify(memory));
response.send();
