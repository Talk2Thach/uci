$(document).ready ->
  geolocation = null

  navigation_url = (address) ->
    address = address.join ", " if '[object Array]' is Object::toString.call address
    address = address.replace /\ /g, "+"

    if /iPhone|iPod|iPad|Mac/.test navigator.platform
      "https://maps.apple.com/?daddr=#{address}"
    else
      "https://maps.google.com/maps?daddr=#{address}"

  get_food = (open = false) ->
    unless geolocation
      alert """
            We cannot detect your current location.
            Please enter the location!
            """
      return

    $.get '/food', geolocation: "#{geolocation.lat},#{geolocation.lng}", (data) ->

      $("#container").empty()

      if data.businesses
        business =  data.businesses[0]
        container = document.getElementById "container"

        img = document.createElement "img"
        img.className = "restaurant"
        img.alt = business.id
        img.src = business.image_url.replace "/ms.", "/l."
        container.appendChild img

        h1 = document.createElement "h1"
        h1.appendChild document.createTextNode business.name
        container.appendChild h1

        yelp_link = document.createElement "a"
        yelp_link.href = business.url
        yelp_link.appendChild document.createTextNode "Yelp"
        container.appendChild yelp_link

        container.appendChild document.createTextNode ", "

        map_link = document.createElement "a"
        map_link.href = navigation_url business.location.display_address
        map_link.appendChild document.createTextNode "Map"
        container.appendChild map_link

        document.location.href = yelp_link.href if open

      return
    return

  address = document.getElementById 'address'

  new google.maps.places.Autocomplete address, types: ['geocode']
    .addListener 'place_changed', ->
      geolocation =
        lat: @getPlace().geometry.location.lat()
        lng: @getPlace().geometry.location.lng()
      get_food()
      return

  google.maps.event.addDomListener address, 'keydown', (event) ->
    event.preventDefault() if event.keyCode is 13
    return

  if navigator.geolocation
    navigator.geolocation.getCurrentPosition (position) ->
      geolocation =
        lat: position.coords.latitude
        lng: position.coords.longitude
      return
    , ->
      "Failed to get a location."
      return
    , enableHighAccuracy: true

  $("#randomize").click (event) ->
    event.preventDefault()
    get_food()
    return

  $("#randomize-open").click (event) ->
    event.preventDefault()
    get_food(true)
    return

  return
