
#include <string>

struct DeviceData
{
    std::string cust_id;
    std::string serial;
    std::string fw_major;
    std::string fw_minor;
    std::string fw_dev;

    std::string send_interval;

    std::string server_date;
    std::string server_time;

    std::string fill_percent;
    std::string pressure_bar;
    std::string fill_liters;
    std::string fill_liters_corr;
    std::string max_press;
    std::string smoothed_dp;
    std::string meas_temp;
    std::string temp_mainboard;

    std::string analog_filllevel;
    std::string analog_pressure;
    std::string analog_ip1;

    std::string digital_input;

    std::string bat_soc;
    std::string bat_voltage;
    std::string bat_current;
    std::string bat_temp;
    std::string bat_soh;
    std::string bat_power;
    std::string bat_full_mah;
    std::string small_heater;
    std::string big_heater;

    std::string iccid;
    std::string signal_percent;
    std::string gps_data;
    std::string network_operator;
    std::string network_tech;

    std::string i2c_err;
    std::string measurementcell_err;
    std::string bms_chip_err;

    std::string wifi_trigger_count;
    std::string backlight_trigger_count;
};

class ParseString
{
public:
    bool parseDeviceData(const char* input, DeviceData& data);
};