var dt = new DateTime();
application.logger.information(dt);
var date = dt.toDate();
application.logger.information(date);

var dt2 = new DateTime(date);
application.logger.information(dt2);

var ldt = new LocalDateTime();
application.logger.information(ldt);
date = ldt.toDate();
application.logger.information(date);

var ldt2 = new LocalDateTime(date);
application.logger.information(ldt2);
