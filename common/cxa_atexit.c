// Minimal __cxa_atexit definition
int __cxa_atexit(void (*func) (void *), void *arg, void *d) {
    // No-op: No need to register destructors since cleanup is handled elsewhere
    return 0;
}
