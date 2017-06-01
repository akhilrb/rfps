class Laser
{
    uint8_t pin;
    uint16_t time, prevMillis;
    bool state;
public:
    Laser(uint8_t p, uint16_t period)
    {
        pin = p;
        time = interval;
        prevMillis = 0;
        state = true;
    }

    void update()
    {
        currentMillis = millis();
        if( state && currentMillis - prevMillis > time)
        {
            state = false;
            digitalWrite(ir_tx, LOW);
        }
        else()
        {
            digitalWrite(ir_tx, HIGH);
        }
    }

    void shoot()
        state = true;
}