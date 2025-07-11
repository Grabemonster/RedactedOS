#include "arp.h"
#include "eth.h"
#include "std/memfunctions.h"

void create_arp_packet(uintptr_t p, uint8_t* src_mac, uint32_t src_ip, uint8_t* dst_mac, uint32_t dst_ip, bool is_request){
    p = create_eth_packet(p, src_mac, is_request ? (uint8_t[]){0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF} : dst_mac, 0x806);
    
    arp_hdr_t* arp = (arp_hdr_t*)p;

    arp->htype = __builtin_bswap16(1);
    arp->ptype = __builtin_bswap16(0x0800);
    arp->hlen = 6;
    arp->plen = 4;
    arp->opcode = __builtin_bswap16(is_request ? 1 : 2);
    memcpy(arp->sender_mac, src_mac, 6);
    arp->sender_ip = __builtin_bswap32(src_ip);
    memcpy(arp->target_mac, dst_mac, 6);
    arp->target_ip = __builtin_bswap32(dst_ip);
}

void arp_populate_response(network_connection_ctx *ctx, arp_hdr_t* arp){
    memcpy(ctx->mac, arp->sender_mac, 6);
    ctx->ip = arp->sender_ip;
}

bool arp_should_handle(arp_hdr_t *arp, uint32_t ip){
    return __builtin_bswap32(arp->target_ip) == ip;
}