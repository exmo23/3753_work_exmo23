#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

/*
 TODO:
 define device buffer size, device name, etc. and other global data structures
 you will need here.
 */
#define BUFFER_SIZE 900
int *opens = 0;
int *closes = 0;

struct file_operations char_driver_file_operations = {
    .owner = THIS_MODULE,
    /*
     TODO:
     add the function pointers to point to corresponding file operations. have a
     look at the linux/include/fs.h file for examples
     */
    .open = simple_char_driver_open,
    .release = simple_char_driver_close,
    .read = simple_char_driver_read,
    .write = simple_char_driver_write,
    .llseek = simple_char_driver_seek,

};

ssize_t char_driver_read(struct file *pfile, char __user *buffer, size_t length,
                         loff_t *offset) {
  /*
   TODO:
   buffer is the userspace buffer to where you are writing the data you
   want to read from the device file

   length is the length of the userspace buffer

   offset will be set to current position of the opened file after reading
   */
        int available = sizeof(pfile) - offset;
        int min_available = min(sizeof(buffer), available);
        unsigned long len = copy_to_user(buffer, pfile, min_available);
        if(len != 0) {
                return -EFAULT;
        }
        else {
                *offset += min_available;
                return min_available;
        }

  return 0;
}

ssize_t char_driver_write(struct file *pfile, const char __user *buffer,
                          size_t length, loff_t *offset) {
  /*
   TODO:
   buffer is the userspace buffer where you are writing the data you want to be
   written into the device file

   length is the length of the userspace buffer

   offset will be set to current position of the opened file
   */
        int available = sizeof(pfile) - offset;
        int min_available = min(sizeof(buffer), available);
        if (!access_ok(VERIFY_WRITE, pfile, min_available) {
                return -EFAULT;
        }
        unsigned long len = copy_from_user(pfile, buffer, min_available);
        if(len != 0) {
                return -EFAULT;
        }
        else {
                *offset += min_available;
                return min_available;
        }

  return length;
}

int char_driver_open(struct inode *pinode, struct file *pfile) {
  /*
   TODO:
   print to the kernel log that the device has been opened, and also print the
   number of times the device has been opened until now.
   */
  printk(%s, "Device opened");
  *opens += 1;
  printk(%s, "Previous opens: %d", opens);
  return 0;
}

int char_driver_close(struct inode *pinode, struct file *pfile) {
  /*
   TODO:
   print to the kernel log that the device has been closed, and also print the
   number of times the device has been closed until now.
   */
  printk(%s, "Device closed");
  *closes += 1;
  printk(%s, "Previous closes: %d", closes);
  return 0;
  return 0;
}

loff_t char_driver_seek(struct file *pfile, loff_t offset, int whence) {
  /*
   TODO:
   update the opened file's position according to the values of offset and
   whence.
   */
  return 0;
}

static int char_driver_init(void) {
  /*
   TODO:
   register the device and print to the kernel log that the init function has
   been called.
   */
        int device = register_chrdev(511, "newdevice", simple_char_driver_file_operations);
        printk("Init function called");
  return 0;
}

static void char_driver_exit(void) {
  /*
   TODO:
   unregister the device using the register_chrdev() function, and print to the
   kernel log that the exit function has been called.
   */
}

/*
 TODO:
 add module_init() and module_exit() functions that point to the corresponding
 init and exit functions of the driver.
*/

