string dayofWeek(stirng day, int k){
    vector<string>days({"Mon", Tue", "Wed", "Thu", "Fri", "Sta", "Sun"});
    int x = 0;
    for(int i = 0; i<7; i++){
        if(days[i].compare(day)==0){
            x =i;break;
        }
    }
    return days[(x+k)%7];
}
