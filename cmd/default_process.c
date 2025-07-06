#include "default_process.h"
#include "types.h"
#include "syscalls/syscalls.h"
#include "input_keycodes.h"
#include "std/string.h"

#define CASE(val, code) case val: return code; break;

char key_to_char(uint8_t keycode){    
    switch (keycode) {
        CASE(0x0, '~')
        CASE(0xE1, '1')
        CASE(0x1F, '2')
        CASE(0x20, '3')
        CASE(0x21, '4')
        CASE(0x22, '5')
        CASE(0x23, '6')
        CASE(0x24, '7')
        CASE(0x25, '8')
        CASE(0x26, '9')
        CASE(0x27, '0')
        CASE(0x2C, ' ')
        CASE(0x14, 'q')
        CASE(0x1A, 'w')
        CASE(0x8, 'e')
        CASE(0x15, 'r')
        CASE(0x17, 't')
        CASE(0x1C, 'y')
        CASE(0x18, 'u')
        CASE(0xC, 'i')
        CASE(0x12, 'o')
        CASE(0x13, 'p')
        CASE(0x4, 'a')
        CASE(0x16, 's')
        CASE(0x7, 'd')
        CASE(0x9, 'f')
        CASE(0xA, 'g')
        CASE(0xB, 'h')
        CASE(0xD, 'j')
        CASE(0xE, 'k')
        CASE(0xF, 'l')
        CASE(0x1D, 'z')
        CASE(0x1B, 'x')
        CASE(0x6, 'c')
        CASE(0x19, 'v')
        CASE(0x5, 'b')
        CASE(0x11, 'n')
        CASE(0x10, 'm')
        default: return '~'; break;
    }
}

uint64_t str_len(const char* str){
    uint64_t len = 0;
    while (str[len] != '\0') len++;
    return len;
}

void proc_func() {
    gpu_size* size = gpu_screen_size();
    gpu_rect rect = (gpu_rect){{10,10},{size->width-20,size->height-20}};
    char *str = (char*)malloc(255);
    str[0] = '\0';
    
    while (1) {
        keypress kp;
        while (read_key(&kp)){
            if (kp.keys[0] == KEY_ESC){
                free(str, 255);
                halt();
            }
            uint64_t stringlenght = str_len(str);
            if (kp.keys[0] == 0x2A){
                if (stringlenght == 0) continue;
                str[stringlenght-1] = '\0';
                continue;
            } 
            char c = key_to_char(kp.keys[0]);
            printf("Stringlenght: %i %x %c", stringlenght, kp.keys[0], c);
            if (stringlenght > 253){
                free(str, 255);
                halt();
            }
            if (c != '~'){
                str[stringlenght] = c;
                str[stringlenght + 1] = '\0';
            }
        }

        clear_screen(0xFFFFFF);
        draw_primitive_rect(&rect, 0x222233);
        string s = string_ca_max((char*)str,255);
        draw_primitive_string(&s,&rect.point,2, 0xFFFFFF);
        free(s.data,s.mem_length);
        gpu_flush_data();
    }
}
