 while (dp[i] != NULL) {
        fprintf(stdout, "arraform %s[%d] (at address %p) points to address %p where this string of %d bytes is stored: '%s'\n", sp, i, &dp[i], sizeof(dp[i]), dp[i]);
        i++;
    }