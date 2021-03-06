/* SPDX-License-Identifier: LGPL-2.1+ */
#pragma once

/***
  This file is part of systemd.

  Copyright 2015 Lennart Poettering
***/

#include <stdbool.h>

#include "cgroup-util.h"
#include "volatile-util.h"

typedef enum MountSettingsMask {
        MOUNT_FATAL              = 1 << 0, /* if set, a mount error is considered fatal */
        MOUNT_USE_USERNS         = 1 << 1, /* if set, mounts are patched considering uid/gid shifts in a user namespace */
        MOUNT_IN_USERNS          = 1 << 2, /* if set, the mount is executed in the inner child, otherwise in the outer child */
        MOUNT_APPLY_APIVFS_RO    = 1 << 3, /* if set, /proc/sys, and /sys will be mounted read-only, otherwise read-write. */
        MOUNT_APPLY_APIVFS_NETNS = 1 << 4, /* if set, /proc/sys/net will be mounted read-write.
                                               Works only if MOUNT_APPLY_APIVFS_RO is also set. */
        MOUNT_INACCESSIBLE_REG   = 1 << 5, /* if set, create an inaccessible regular file first and use as bind mount source */
} MountSettingsMask;

typedef enum CustomMountType {
        CUSTOM_MOUNT_BIND,
        CUSTOM_MOUNT_TMPFS,
        CUSTOM_MOUNT_OVERLAY,
        _CUSTOM_MOUNT_TYPE_MAX,
        _CUSTOM_MOUNT_TYPE_INVALID = -1
} CustomMountType;

typedef struct CustomMount {
        CustomMountType type;
        bool read_only;
        char *source; /* for overlayfs this is the upper directory */
        char *destination;
        char *options;
        char *work_dir;
        char **lower;
        char *rm_rf_tmpdir;
} CustomMount;

CustomMount* custom_mount_add(CustomMount **l, size_t *n, CustomMountType t);
void custom_mount_free_all(CustomMount *l, size_t n);
int custom_mount_prepare_all(const char *dest, CustomMount *l, size_t n);

int bind_mount_parse(CustomMount **l, size_t *n, const char *s, bool read_only);
int tmpfs_mount_parse(CustomMount **l, size_t *n, const char *s);
int overlay_mount_parse(CustomMount **l, size_t *n, const char *s, bool read_only);

int mount_all(const char *dest, MountSettingsMask mount_settings, uid_t uid_shift, uid_t uid_range, const char *selinux_apifs_context);
int mount_sysfs(const char *dest, MountSettingsMask mount_settings);

int mount_cgroups(const char *dest, CGroupUnified unified_requested, bool userns, uid_t uid_shift, uid_t uid_range, const char *selinux_apifs_context, bool use_cgns);
int mount_systemd_cgroup_writable(const char *dest, CGroupUnified unified_requested);

int mount_custom(const char *dest, CustomMount *mounts, size_t n, bool userns, uid_t uid_shift, uid_t uid_range, const char *selinux_apifs_context);

int setup_volatile(const char *directory, VolatileMode mode, bool userns, uid_t uid_shift, uid_t uid_range, const char *selinux_apifs_context);
int setup_volatile_state(const char *directory, VolatileMode mode, bool userns, uid_t uid_shift, uid_t uid_range, const char *selinux_apifs_context);

int pivot_root_parse(char **pivot_root_new, char **pivot_root_old, const char *s);
int setup_pivot_root(const char *directory, const char *pivot_root_new, const char *pivot_root_old);
