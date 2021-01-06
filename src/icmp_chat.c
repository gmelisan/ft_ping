/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp_chat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:38:11 by gmelisan          #+#    #+#             */
/*   Updated: 2021/01/06 21:39:28 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static ushort			get_checksum(void *b, int len)
{
    ushort *buf;
    uint sum;
    ushort result;

	buf = (ushort *)b;
	sum = 0;
    while (len > 1)
	{
        sum += *buf++;
		len -= 2;
	}
    if (len == 1)
        sum += *(uchar*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return (result);
}

struct s_icmp_packet	create_icmp(int seq, int id, char *data)
{
	struct s_icmp_packet	pkt;

	ft_memset(&pkt, 0, sizeof(pkt));
	pkt.header.type = ICMP_ECHO;
	pkt.header.code = 0;
	pkt.header.un.echo.sequence = seq;
	pkt.header.un.echo.id = id;
	ft_memcpy(pkt.data, data, ICMP_DATA_SIZE);
	pkt.header.checksum = get_checksum(&pkt, sizeof(pkt));
	return (pkt);
}

int						send_icmp(int sck, struct sockaddr_in sa,
									struct s_icmp_packet pkt)
{
	int ret;
	
	ret = sendto(sck, &pkt, sizeof(pkt), 0, (struct sockaddr *)&sa, sizeof(sa));
	if (ret < 0)
		return (error("sendto(): %s", strerror(errno)));
	if (ret < ICMP_PACKET_SIZE)
		return (error("sendto(): sended incomplete data"));
	//ft_printf("send: type %d, code %d, id %d, seq %d, data %s\n",
	//		  pkt.header.type, pkt.header.code, pkt.header.un.echo.id,
	//		  pkt.header.un.echo.sequence, pkt.data);
	//ft_printf("%d bytes sent\n", ret);
	return (ret);
}

int						receive_icmp(int sck, struct sockaddr_in sa,
								struct s_icmp_packet *pkt)
{
	int ret;
	struct msghdr msg;
	struct iovec io;
	char buf[ICMP_PACKET_SIZE + IP_HEADER_SIZE + 128];

	ft_memset(&msg, 0, sizeof(msg));
	io.iov_base = buf;
	io.iov_len = sizeof(buf);
	msg.msg_name = &sa;
	msg.msg_namelen = sizeof(sa);
	msg.msg_iov = &io;
	msg.msg_iovlen = 1;
	ret = recvmsg(sck, &msg, 0);
	if (ret < 0)
		return (error("recvmsg(): %s\n", strerror(errno)));
	if (ret != ICMP_PACKET_SIZE + IP_HEADER_SIZE)
		return (error("recvmsg(): received wrong number of bytes"));
	*pkt = *(struct s_icmp_packet *)(buf + IP_HEADER_SIZE);
	//ft_printf("rcv: type %d, code %d, id %d, seq %d, data %s\n",
	//		  pkt->header.type, pkt->header.code, pkt->header.un.echo.id,
	//		  pkt->header.un.echo.sequence, pkt->data);
	return (ICMP_PACKET_SIZE);
}
