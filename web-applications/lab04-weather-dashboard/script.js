class WeatherApp {
    constructor(key, resultContainer){
        this.key = key;
        this.resultContainer = resultContainer;
        this.currentLink = `https://api.openweathermap.org/data/2.5/weather?q={city}&appid=${this.key}&units=metric&lang=pl`;
        this.foreCastLink = `https://api.openweathermap.org/data/2.5/forecast?q={city}&appid=${this.key}&units=metric&lang=pl`;
        this.currentWeather = undefined; 
        this.foreCastWeather = undefined;
    }

    getWeather(city){
        this.resultContainer.innerHTML = "";
        this.getCurrentWeather(city);
        this.getForeCastWeather(city);

        
    }

    getCurrentWeather(city){
        let url = this.currentLink.replace("{city}", city);
        let request = new XMLHttpRequest();
        request.open("GET", url, true);
        request.addEventListener("load", () => {
            console.log(JSON.parse(request.responseText));
            this.currentWeather = JSON.parse(request.responseText);
        });
        request.send();
    }

    getForeCastWeather(city){
        let url = this.foreCastLink.replace("{city}", city);
        fetch(url)
        .then(response => {
            return response.json();
        })
        .then(data => {
            console.log(data.list);
            this.foreCastWeather = data.list;
            this.drawWeather();
        })
        ;
    }

    createWeatherBlock(iconCode, temp, feelsTemp, dateStr, wind, visib, desc){

        const weatherBlock = document.createElement("div");
        weatherBlock.classList.add("weather-block");

        const icon = document.createElement("img");
        icon.classList.add("weather-icon");
        icon.setAttribute("src",`http://openweathermap.org/img/wn/${iconCode}@2x.png`);
        weatherBlock.appendChild(icon);

        const temperature = document.createElement("p");
        temperature.innerText = `${(parseFloat(temp)).toFixed(1)} °C`;
        temperature.classList.add("temperature");
        weatherBlock.appendChild(temperature);

        const feelsTemperature = document.createElement("p");
        feelsTemperature.innerText = `Odczuwalna: ${feelsTemp} °C`;
        feelsTemperature.classList.add("feels-temperature");
        feelsTemperature.classList.add("text");
        weatherBlock.appendChild(feelsTemperature);

        const dateString = document.createElement("p");
        dateString.innerText = `${dateStr}`;
        dateString.classList.add("date");
        weatherBlock.appendChild(dateString);

        const windSpeed = document.createElement("p");
        windSpeed.innerHTML = `
            <i class="fa-solid fa-wind"></i> ${(wind * 3.6).toFixed(2)} km/h
        `;
        windSpeed.classList.add("wind-speed");
        windSpeed.classList.add("text");
        weatherBlock.appendChild(windSpeed);

        const visibility = document.createElement("p");
        visibility.innerHTML = `
            <i class="fa-solid fa-eye"></i> ${visib} km
        `;
        visibility.classList.add("visibility");
        visibility.classList.add("text");
        weatherBlock.appendChild(visibility);

        const summary = document.createElement("p");
        let windLevel = "";
        if(wind <= 11) windLevel = "słaby";
        else if (wind > 11 && wind < 40) windLevel = "umiarkowany";
        else windLevel = "silny";
        let visibilityLevel = "";
        if(visib <= 2) visibilityLevel = "słaba";
        else if (visib >2 && visib < 10) visibilityLevel = "umiarkowana";
        else visibilityLevel = "dobra";
        summary.innerHTML = `
            ${desc}, wiatr: ${windLevel}, widoczność: ${visibilityLevel} 
        `;
        summary.classList.add("summary");
        weatherBlock.appendChild(summary);
        
        return weatherBlock;
    }

    drawWeather(){
        if(this.currentWeather){
            const date = new Date(this.currentWeather.dt * 1000);
            const weatherBlock = this.createWeatherBlock(
                `${this.currentWeather.weather[0].icon}`, 
                `${this.currentWeather.main.temp}`, 
                `${this.currentWeather.main.feels_like}`, 
                `${date.toLocaleDateString("pl-PL")} ${date.toLocaleTimeString("pl-PL")}`, 
                `${this.currentWeather.wind.speed}`, 
                `${this.currentWeather.visibility/1000}`, 
                `${this.currentWeather.weather[0].description}`
            );
            this.resultContainer.appendChild(weatherBlock);
        }

        if(this.foreCastWeather){
            for (const day of this.foreCastWeather){
                const date = new Date(day.dt * 1000);
                const weatherBlock = this.createWeatherBlock(
                    `${day.weather[0].icon}`, 
                    `${day.main.temp}`, 
                    `${day.main.feels_like}`, 
                    `${date.toLocaleDateString("pl-PL")} ${date.toLocaleTimeString("pl-PL")}`, 
                    `${day.wind.speed}`, 
                    `${day.visibility/1000}`, 
                    `${day.weather[0].description}`
            );
            this.resultContainer.appendChild(weatherBlock);
            }
            this.drawStyles();
        }
    }

    drawStyles(){
        if(this.currentWeather){
            const body = document.querySelector("body");
            const h1 = document.querySelector("h1");
            const cityInput = document.getElementById("city-input");
            const weatherBlocks = document.querySelectorAll(".weather-block");

            if(this.currentWeather.weather[0].icon[2] == 'n'){
                body.className = '';
                body.classList.add("bodyNight");

                h1.className="";
                h1.classList.add("h1Night");

                cityInput.className = '';
                cityInput.classList.add("cityInputNight");

                checkBtn.className='';
                checkBtn.classList.add("checkBtnNight");

                weatherBlocks.forEach(weatherBlock => {
                    weatherBlock.className="";
                    weatherBlock.classList.add("weather-block");
                    weatherBlock.classList.add("weatherBlockNight");
                })
            }

            else{
                body.className = '';
                body.classList.add("bodyDefault");

                h1.className="";
                h1.classList.add("h1Default");

                cityInput.className = '';
                cityInput.classList.add("cityInputDefault");

                checkBtn.className='';
                checkBtn.classList.add("checkBtnDefault");

                weatherBlocks.forEach(weatherBlock => {
                    weatherBlock.className="";
                    weatherBlock.classList.add("weather-block");
                    weatherBlock.classList.add("weatherBlockDefault");
                })
            }
            


        }

    }
}

const resultContainer = document.getElementById("weather-container");
const checkBtn = document.getElementById("check-btn");

const key = "e512e58db14bb33c8cadfd2c77e9ae9f";
const app = new WeatherApp(key, resultContainer);
checkBtn.addEventListener("click", () => app.getWeather(document.getElementById("city-input").value));
