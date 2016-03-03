express = require "express"
Yelp = require "yelp"
app = express()

yelp = new Yelp JSON.parse process.env.YELP_OAUTH_CLIENT_CREDENTIALS

app.use express.static 'public'

app.get '/food', (req, res) ->
  yelp.search
    term: 'food'
    ll: req.query.geolocation
  .then (data) ->
    if data.businesses
      random = Math.floor(Math.random() * data.businesses.length)
      data.businesses =  [data.businesses[random]]
    res.json data
  .catch (err) ->
    res.json err

app.listen (process.env.PORT or 3000), ->
  console.log("Random Eater app listening on port #{process.env.PORT or 3000}!")

