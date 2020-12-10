var session = new DBSession('SQLite', 'test.db');

session.executeNonQuery('CREATE TABLE IF NOT EXISTS test (id INTEGER, value VARCHAR)');

for (var i = 0; i < 10; i++)
{
	const random = UUID.createRandom().toString();
	session.executeNonQuery('INSERT INTO test VALUES(?, ?)', i, random);
}

var rs = session.execute('SELECT * FROM test');

for (var row = 0; row < rs.rowCount; row++)
{
	for (var col = 0; col < rs.columnCount; col++)
	{
		const name = rs.getName(col);
		const value = rs.getValue(col, row);
		console.log('%d %s=%s', row, name, value);
	}
}

rs.close();