var httpRequest = new HTTPRequest('GET', 'https://macchina.io');
httpRequest.timeout = 10.0;
httpRequest.send(
	function(result)
	{
		if (result.error)
		{
			console.error(result.error);
		}
		else
		{
			console.log(result.response.status, " ", result.response.reason);
			console.log(result.response.content);
		}
	}
);
