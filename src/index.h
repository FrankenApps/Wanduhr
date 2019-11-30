const char MAIN_page[] /*PROGMEM*/ = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <!-- Required meta tags-->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, minimum-scale=1, user-scalable=no, minimal-ui, viewport-fit=cover">
    <meta name="apple-mobile-web-app-capable" content="yes">
    <meta name="apple-mobile-web-app-status-bar-style" content="default">
    <link rel="apple-touch-icon" href="https://raw.githubusercontent.com/FrankenApps/ArduinoClockManager/master/icons/logo2.png">
    <link rel="shortcut icon" type="image/x-icon" href="https://raw.githubusercontent.com/FrankenApps/ArduinoClockManager/master/icons/logo.png">
    <!-- Color theme for statusbar -->
    <meta name="theme-color" content="#2196f3">
    <!-- Your app title -->
    <title>Wanduhr</title>
    <!-- Path to Framework7 Library Bundle CSS -->
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/framework7/4.2.2/css/framework7.bundle.min.css" integrity="sha256-WXIZJ6YBOy08rAXlqh1EvpWy7DEYX+9nHX8du4PJxVM=" crossorigin="anonymous" />
    <!-- Path to your custom app styles-->
    <style>
    #colorBox {
      width: 1.5em;
      height: 1.5em;
      padding-bottom: 0.4em;
      border: none;
    }
    </style>
    <!-- JQuery -->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.3.1/jquery.min.js" integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8=" crossorigin="anonymous"></script>
    <!-- D3.js -->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/d3/5.9.2/d3.min.js" integrity="sha256-k9RyZhvMj2bg0fd8L3IE41t0HpTXnivMoePN/Ksq250=" crossorigin="anonymous"></script>
  </head>
  <body>
    <!-- App root element -->
    <div id="app">
      <!-- Statusbar overlay -->
      <div class="statusbar"></div>

      <!-- Your main view, should have "view-main" class -->
      <div class="view view-main">
        <!-- Initial Page, "data-name" contains page name -->
        <div data-name="home" class="page">

          <!-- Top Navbar -->
          <div class="navbar">
            <div class="navbar-inner">
              <div class="title center sliding">Wanduhr Controller</div>
            </div>
          </div>

          <!-- Bottom Toolbar -->
          <div class="toolbar toolbar-bottom">
            <div class="toolbar-inner">
              
            </div>
          </div>

          <!-- Scrollable page content -->
          <div class="page-content">
            <div class="block-title">Settings</div>
            <div class="list simple-list">
              <ul>
                <li>
                  <span>Clock Mode</span>
                  <label class="toggle toggle-init color-black" id="uhrmodusToggle">
                    <input type="checkbox" checked disabled>
                    <span class="toggle-icon"></span>
                  </label>
                </li>
                <li>
                  <span style="color: darkgray">Stopwatch Mode</span>
                  <label class="toggle toggle-init color-blue" id="stoppuhrToggle">
                    <input type="checkbox" disabled>
                    <span class="toggle-icon"></span>
                  </label>
                </li>
                <li>
                  <span>Daylight Savings</span>
                  <label class="toggle toggle-init color-red" id="sommerzeitToggle">
                    <input type="checkbox">
                    <span class="toggle-icon"></span>
                  </label>
                </li>              
              </ul>
            </div>

            <div class="block-title">Overview</div>
            <div class="list simple-list inline-labels no-hairlines-md">
              <ul>
                <li>
                  <span>Time</span>
                  <label class="color-black">
                    <span id="timeDisplay">00:00:00</span>
                  </label>
                </li>      
                <li class="item-content item-input">
                  <div class="item-inner">
                    <div class="row" style="width: 100%">
                        <div class="item-title color-black col-40">NTP-Provider</div>
                        <div class="item-input-wrap col-60" style="padding-top: 0.4em">
                          <input type="text" placeholder="New NTP-Provider" id="ntpProvider" value="europe.pool.ntp.org">
                          <span class="input-clear-button" style="padding-top: 0.4em"></span>
                        </div>
                    </div>
                    
                  </div>
                </li>       
              </ul>
            </div>

            <div class="block-title">Design</div>
            <div class="list simple-list">
              <ul>
                <li>
                  <div class="item-cell flex-shrink-3">
                    <!-- range slider, enable labels -->
                    <div class="range-slider range-slider-init color-red" data-label="true" id="sliderRed">
                      <input type="range" min="0" max="255" step="1" value="50">
                    </div>
                  </div>
                </li>
                <li>
                  <div class="item-cell flex-shrink-3">
                    <!-- range slider, enable labels -->
                    <div class="range-slider range-slider-init color-green" data-label="true" id="sliderGreen">
                      <input type="range" min="0" max="255" step="1" value="200">
                    </div>
                  </div>
                </li>
                <li>
                  <div class="item-cell flex-shrink-3">
                    <!-- range slider, enable labels -->
                    <div class="range-slider range-slider-init color-blue" data-label="true" id="sliderBlue">
                      <input type="range" min="0" max="255" step="1" value="150">
                    </div>
                  </div>
                </li>
                <li>
                  <div class="label-cell">Select clock hand color <button id="colorBox" disabled></button> for:</div>
                </li>
                  <li>
                  <div class="item-cell">
                    
                      <div class="row">
                          <!-- Each "cell" has col-[width in percents] class -->
                          <div class="col-33"><p>Seconds: <label class="radio"><input type="radio" name="color-radio" value="1" id="secColor"><i class="icon-radio"></i></label></p></div>
                          <div class="col-33"><p>Minutes: <label class="radio"><input type="radio" name="color-radio" value="2" id="minColor"><i class="icon-radio"></i></label></p></div>
                          <div class="col-33"><p>Hours: <label class="radio"><input type="radio" name="color-radio" value="3" id="hourColor"><i class="icon-radio"></i></label></p></div>
                      </div>
                    </div>
                </li>
                <li>
                    <div class="label-cell">Edit Helpers:</div>
                  </li>
                    <li>
                    <div class="item-cell">
                      
                        <div class="row">
                            <!-- Each "cell" has col-[width in percents] class -->
                            <div class="col-50"><p>Color: <label class="radio"><input type="radio" name="color-radio" value="4" id="helperColor"><i class="icon-radio"></i></label></p></div>
                            <div class="col-50"><p>Show Helpers: <label class="toggle toggle-init color-lightblue" id="helperToggle">
                                <input type="checkbox" checked>
                                <span class="toggle-icon"></span>
                              </label></p></div>
                        </div>
                      </div>
                  </li>
              </ul>
              </div>
              <div class="block-title">Brightness</div>
            <div class="list simple-list">
              <ul>
                  <li>
                      <div class="item-cell">
                          <div class="item-cell flex-shrink-3">
                              <div class="row">
                                <div class="col-35">
                                    <label style="display: inline;">Clock Hands: </label>
                                </div>
                                <div class="col-65" style="padding-top: 1em">
                                    <div class="range-slider range-slider-init color-gray" data-label="true" id="pointerBrightness">
                                      <input type="range" min="0" max="255" step="1" value="128">
                                    </div>
                                </div> 
                              </div>
                            </div>
                        </div>  
                    </li>
                    <li>
                        <div class="item-cell">
                            <div class="item-cell flex-shrink-3">
                                <div class="row">
                                  <div class="col-35">
                                      <label style="display: inline;">Helpers: </label>
                                  </div>
                                  <div class="col-65" style="padding-top: 1em">
                                      <div class="range-slider range-slider-init color-gray" data-label="true" id="helperBrightness">
                                        <input type="range" min="0" max="255" step="1" value="16">
                                      </div>
                                  </div> 
                                </div>
                              </div>
                          </div>  
                      </li>
              </ul>
            


              <div class="block-title">Preview</div>
            <div class="center sliding">
              <div style="width: 100%; max-width: 600px;" id="svgContainer">

              </div>
            </div>
          </div>

          <div class="list simple-list">
            <ul>
              <li>
                <div class="item-cell flex-shrink-3">
                    <button class="button" id="applySettings">Apply Settings</button>
                </div>
              </li>
              <li>
                  <div class="item-cell flex-shrink-3 color-red">
                      <button class="button">Discard Changes</button>
                  </div>
              </li>
            </ul>
          </div>


            </div>

            

        </div>
      </div>
    </div>
    <!-- Path to Framework7 Library Bundle JS-->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/framework7/4.2.2/js/framework7.bundle.min.js" integrity="sha256-7WPUs16amb62/mQE5xsmbGu3XuNgfATwAqVZ/hzNvCc=" crossorigin="anonymous"></script>
    
    <script>
        var app = new Framework7({
        // App root element
        root: '#app',
        // App Name
        name: 'Wall-Clock Controller',
        // App id
        id: 'de.frankenapps.wallclockcontroler',
        });

        var mainView = app.views.create('.view-main');


        //own js routine
        let showHelperToggle, rangeRed, rangeGreen, rangeBlue, clockModeToggle, stopWatchToggle, daylightSavingsToggle;

        let secondsColor = 'rgb(0,255,0)';
        let minutesColor = 'rgb(255,0,0)';
        let hoursColor = 'rgb(0,0,255)';
        let helperColor = 'rgb(238,238,238)';

        $(document).ready(function() {
          //initalize Framework7 components
          showHelperToggle = app.toggle.get('#helperToggle');
          clockModeToggle = app.toggle.get('#uhrmodusToggle');
          stopWatchToggle = app.toggle.get('#stoppuhrToggle');
          daylightSavingsToggle = app.toggle.get('#sommerzeitToggle');
          rangeRed = app.range.get('#sliderRed');
          rangeGreen = app.range.get('#sliderGreen');
          rangeBlue = app.range.get('#sliderBlue');
          rangeHelperBrightness = app.range.get('#helperBrightness');
          rangePointerBrightness = app.range.get('#pointerBrightness');

            //find out if daylight savings is active currently and apply it as the default setting
            if(new Date().getTimezoneOffset() == -120){
                daylightSavingsToggle.toggle();
            }
        
          //get current settings from the esp8266
          $.post("/currentSettings", function(data) {
            console.log(data);
            let dataArray = data.split(';');
            secondsColor = dataArray[0];
            minutesColor = dataArray[1];
            hoursColor = dataArray[2];
            helperColor = dataArray[3];
            if (dataArray[4] == 'false') {
              showHelperToggle.toggle();
            }
            if (dataArray[5] == 'false') {
              daylightSavingsToggle.toggle();
            }
            if (dataArray[6] == 'false') {
              clockModeToggle.toggle();
            }
            if(dataArray[7] == 'true'){
              stopWatchToggle.toggle();
            }
            $('#ntpProvider').val(dataArray[8]);
            rangeHelperBrightness.setValue(parseInt(dataArray[9]));
            rangePointerBrightness.setValue(parseInt(dataArray[10]));
            $('#secColor + i').css('border-color', secondsColor); //overrides the statement below
            $('#minColor + i').css('border-color', minutesColor);
            $('#hourColor + i').css('border-color', hoursColor);
            $('#helperColor + i').css('border-color', helperColor);
            });
          
          $('#secColor + i').css('border-color', secondsColor);
          $('#minColor + i').css('border-color', minutesColor);
          $('#hourColor + i').css('border-color', hoursColor);
          $('#helperColor + i').css('border-color', helperColor);
          
          //init the svg
          $.get('https://raw.githubusercontent.com/FrankenApps/Wanduhr_support_files/master/icons/icon_transparent.svg?sanitize=true', function(data) {
            $('#svgContainer').append(data.documentElement);
            var timeUpdater = setInterval(updateClock, 100);
          });
        
          $('#applySettings').on('click', function() {
            $.post('/updateSettings', { settings: `${secondsColor};${minutesColor};${hoursColor};${helperColor};${showHelperToggle.checked};${daylightSavingsToggle.checked};${clockModeToggle.checked};${stopWatchToggle.checked};${$('#ntpProvider').val()};${rangeHelperBrightness.value};${rangePointerBrightness.value};`});
          });
        });

        function updateClock() {
            //get new time
            d = new Date();
            let seconds = d.getSeconds();
            let minutes = d.getMinutes();
            let hours = d.getHours();
            let time_offset = 0;

            //calculate daylight savings toggle
            if(new Date().getTimezoneOffset() == -120 && daylightSavingsToggle.checked == false){
                time_offset = -1;
            }   else if(new Date().getTimezoneOffset() == -60 && daylightSavingsToggle.checked == true){
                time_offset = 1;
            }

            if (hours+time_offset>11) {
                hours -= 12;
            }
        
          $('#timeDisplay').html(
            `${('0' + String(d.getHours()+time_offset)).slice(-2)}:${('0' + String(minutes)).slice(-2)}:${('0' + String(seconds)).slice(-2)}` //because I use 24h format in that display
          );
        
          //get user configurations
          let showHelper = showHelperToggle.checked;
        
          let currentUserColor = `rgb(${rangeRed.value},${rangeGreen.value},${rangeBlue.value})`;
          $('#colorBox').css('background-color', currentUserColor);
          $(':root').css('--f7-radio-active-color', currentUserColor);
        
          switch (parseInt($('input:checked[name=color-radio]').val())) {
            case 1:
              secondsColor = currentUserColor;
              $('input:checked[name=color-radio] + i').css('border-color', secondsColor);
              break;
            case 2:
              minutesColor = currentUserColor;
              $('input:checked[name=color-radio] + i').css('border-color', minutesColor);
              break;
            case 3:
              hoursColor = currentUserColor;
              $('input:checked[name=color-radio] + i').css('border-color', hoursColor);
              break;
            case 4:
              helperColor = currentUserColor;
              $('input:checked[name=color-radio] + i').css('border-color', helperColor);
              break;
            default:
              break;
          }
        
          //reset all pixels
          d3.selectAll('.led').style('fill', '#BDC3C7');
          d3.selectAll('.led').style('opacity', 1);
        
          //apply the styling configuration fitting for the current time
          if (showHelper) {
            d3.select('#led0').style('fill', helperColor);
            d3.select('#led15').style('fill', helperColor);
            d3.select('#led30').style('fill', helperColor);
            d3.select('#led45').style('fill', helperColor);

            var opacity = 0;  //Otherwise helpers would become invisible when they are not in reality.
            if(parseFloat(rangeHelperBrightness.value) > 70){
              opacity = parseFloat(rangeHelperBrightness.value)/255;
            } else if (parseFloat(rangeHelperBrightness.value) == 0){
              opacity = 0;
            } else{
              opacity = parseFloat(225/255);
            }

            d3.select('#led0').style('opacity', opacity);
            d3.select('#led15').style('opacity', opacity);
            d3.select('#led30').style('opacity', opacity);
            d3.select('#led45').style('opacity', opacity);
          }
        
          d3.select('#led' + String(seconds)).style('fill', secondsColor);
          d3.select('#led' + String(minutes)).style('fill', minutesColor);
          d3.select('#led' + String((hours+time_offset)*5)).style('fill', hoursColor);

          var opacity = 0;  //Otherwise clock hands would become invisible when they are not in reality.
          if(parseFloat(rangePointerBrightness.value) > 70){
            opacity = parseFloat(rangePointerBrightness.value)/255;
          } else if (parseFloat(rangePointerBrightness.value) == 0){
            opacity = 0;
          } else{
            opacity = parseFloat(70/255);
          }

          d3.select('#led' + String(seconds)).style('opacity', opacity);
          d3.select('#led' + String(minutes)).style('opacity', opacity);
          d3.select('#led' + String((hours+time_offset)*5)).style('opacity', opacity);   
        }
    </script>
  </body>
</html>
)=====";