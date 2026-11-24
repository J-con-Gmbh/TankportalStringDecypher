#include "ParseString.h"

bool ParseString::parseDeviceData(const char* input, DeviceData& data)
{
    // Reset all fields to empty strings
    data = DeviceData{};

    if (!input)
        return false;

    std::string str(input);
    // If the 1st Symbol is a { delete it
    if (str.find("{") == 0) str = str.substr(1, str.length());
    //likewise delete the last "}"
    if (str.find("}") == str.length()) str = str.substr(0, str.length() - 1);
    auto getField = [&](const std::string& start,
        const std::string& end = "") -> std::string
        {
            size_t pos = str.find(start);

            if (pos == std::string::npos)
                return "";

            pos += start.length();

            size_t endPos = end.empty()
                ? std::string::npos
                : str.find(end, pos);

            return str.substr(pos, endPos - pos);
        };


    // Split only where individual field markers define boundaries
    std::string id  = getField("",      "&PA=");
    std::string pa  = getField("&PA=",  "&TI=");
    std::string ti  = getField("&TI=",  "&MES=");
    std::string mes = getField("&MES=", "&AL=");
    std::string al  = getField("&AL=",  "&DI=");
    std::string di  = getField("&DI=",  "&BAT=");
    std::string bat = getField("&BAT=", "&LTE=");
    std::string lte = getField("&LTE=", "&ERR=");
    std::string err = getField("&ERR=", "&DBU=");
    std::string dbu = getField("&DBU=");

    // ID
    size_t p1 = id.find(';');
    size_t p2 = id.find(';', p1 + 1);

    if (p1 == std::string::npos || p2 == std::string::npos)
        return false;

    data.cust_id = id.substr(0, p1);
    data.serial = id.substr(p1 + 1, p2 - p1 - 1);

    std::string firmware = id.substr(p2 + 1);

    size_t f1 = firmware.find('.');
    size_t f2 = firmware.find('.', f1 + 1);

    if (f1 == std::string::npos || f2 == std::string::npos)
        return false;

    data.fw_major = firmware.substr(0, f1);
    data.fw_minor = firmware.substr(f1 + 1, f2 - f1 - 1);
    data.fw_dev = firmware.substr(f2 + 1);

    // PA
    data.send_interval = pa;

    // TI
    size_t t = ti.find(',');
    if (t != std::string::npos)
    {
        data.server_date = ti.substr(0, t);
        data.server_time = ti.substr(t + 1);
    }

    // MES

    auto assign = [](const std::string& s, size_t index) -> std::string
        {
            size_t start = 0;

            for (size_t i = 0; i < index; ++i)
            {
                start = s.find(';', start);

                if (start == std::string::npos)
                    return "";

                ++start;
            }

            if (start >= s.size())
                return "";

            size_t end = s.find(';', start);

            return s.substr(start, end - start);
        };

    data.fill_percent = assign(mes, 0);
    data.pressure_bar = assign(mes, 1);
    data.fill_liters = assign(mes, 2);
    data.fill_liters_corr = assign(mes, 3);
    data.max_press = assign(mes, 4);
    data.smoothed_dp = assign(mes, 5);
    data.meas_temp = assign(mes, 6);
    data.temp_mainboard = assign(mes, 7);

    // AL
    data.analog_filllevel = assign(al, 0);
    data.analog_pressure = assign(al, 1);
    data.analog_ip1 = assign(al, 2);

    // DI
    data.digital_input = di;

    // BAT (optional)
    if (!bat.empty())
    {
        data.bat_soc = assign(bat, 0);
        data.bat_voltage = assign(bat, 1);
        data.bat_current = assign(bat, 2);
        data.bat_temp = assign(bat, 3);
        data.bat_soh = assign(bat, 4);
        data.bat_power = assign(bat, 5);
        data.bat_full_mah = assign(bat, 6);
        data.small_heater = assign(bat, 7);
        data.big_heater = assign(bat, 8);
    }

    // LTE
    data.iccid = assign(lte, 0);
    data.signal_percent = assign(lte, 1);
    data.gps_data = assign(lte, 2);
    data.network_operator = assign(lte, 3);
    data.network_tech = assign(lte, 4);

    // ERR
    data.i2c_err = assign(err, 0);
    data.measurementcell_err = assign(err, 1);
    data.bms_chip_err = assign(err, 2);

    // DBU
    data.wifi_trigger_count = assign(dbu, 0);
    data.backlight_trigger_count = assign(dbu, 1);

    return true;
}