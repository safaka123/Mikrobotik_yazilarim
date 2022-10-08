var request = require("request");
var options = { 
  method: 'GET',
  url: 'https://api.sinric.pro/api/v1/activitylogs/device/63304fab36b44d06d4c4ff0d',
  headers: 
  {   'Authorization': 'Bearer <TOKEN HERE>',
      'Content-Type': 'application/x-www-form-urlencoded' 
  }
};

request(options, function (error, response, body) {
  if (error) throw new Error(error);
  console.log(body);
});
