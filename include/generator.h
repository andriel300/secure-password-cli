#pragma once

char *generate_password(int length, int use_upper, int use_lower,
                        int use_numbers, int use_symbols, int min_numbers,
                        int min_symbols);
