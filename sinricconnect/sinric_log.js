var request = require("request");
var options = { 
  method: 'GET',
  url: 'https://api.sinric.pro/api/v1/activitylogs/device/5c5e726095bd1817e07ab3ac',
  headers: 
  {   'Authorization': 'Bearer <TOKEN HERE>',
      'Content-Type': 'application/x-www-form-urlencoded' 
  }
};

request(options, function (error, response, body) {
  if (error) throw new Error(error);
  console.log(body);
});
