
#ifndef _NETLINK_TEMPL_H_
#define _NETLINK_TEMPL_H_

// for kernel module
void scull_create_netlink(void);
void scull_remove_netlink(void);

// it should be same in kernel and user
#define NETLINK_USER 31


#endif /* _NETLINK_TEMPL_H_ */
