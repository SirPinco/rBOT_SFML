if (FUT_Saving.wait_for(chrono::milliseconds(0)) != future_status::ready)
FUT_Saving.wait();