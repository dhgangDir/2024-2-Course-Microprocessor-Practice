// led.h

void led_init(void); 
void led_on_all(void); 
void led_off_all(void); 
void led_on(int led_no);
void led_off(int led_no);
void led_set(int led_mask);
int get_led();
