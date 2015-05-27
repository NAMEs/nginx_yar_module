#include <ngx_yar/yar.h>
#include <stdio.h>
#include <string.h>

/* somewhat unix-specific */
#include <sys/time.h>
#include <unistd.h>

/* curl stuff */
#include <curl/curl.h>


#define HANDLECOUNT 1   /* Number of simultaneous transfers */
#define HTTP_HANDLE 0   /* Index for the HTTP transfer */
#define FTP_HANDLE 1    /* Index for the FTP transfer */


void yar_method_test(yar_request *request, yar_response *response, void *cookie){

    usleep(10000);

    yar_packager *misko_success_pack = NULL;

    misko_success_pack = yar_pack_start_map(3);
    yar_pack_push_string(misko_success_pack,"err_code",sizeof("err_code") -1);
    yar_pack_push_long(misko_success_pack,0);

    yar_pack_push_string(misko_success_pack,"err_msg",sizeof("err_msg") -1);
    yar_pack_push_string(misko_success_pack,"success",sizeof("success") -1);

    yar_pack_push_string(misko_success_pack,"data",sizeof("data") -1);
    yar_pack_push_map(misko_success_pack,1);

    yar_pack_push_string(misko_success_pack,"count",sizeof("count") -1);
    yar_pack_push_long(misko_success_pack,1);
    yar_response_set_retval(response,misko_success_pack);

    yar_pack_free(misko_success_pack);


}


void yar_method_echo(yar_request *request,yar_response *response, void *cookie){

    yar_packager *packager = NULL;

    packager = yar_pack_start_map(3);

    {

        yar_pack_push_string(packager,"request_id",sizeof("request_id") -1);
        yar_pack_push_long(packager,request->id);

    }

    {

        yar_pack_push_string(packager,"request_method",sizeof("request_method") -1);
        yar_pack_push_string(packager,request->method,request->mlen);

    }

    {
        const yar_data *parametersData = yar_request_get_parameters(request);
        yar_pack_push_string(packager,"request_parameters",sizeof("request_parameters") -1);
        yar_pack_push_data(packager,parametersData);

    }

    yar_response_set_retval(response,packager);
    yar_pack_free(packager);

}



void yar_method_send_big_data(yar_request *request, yar_response *response, void *cookie){

    int size = 10000000;

    char *log = (char *)calloc(sizeof(char) * size,1);

    int i=0;

    for(i=0;i<size;i++){

       log[i] = 'a';

    }

    log[size] = 0;

    yar_packager *misko_success_pack = NULL;

    misko_success_pack = yar_pack_start_map(3);
    yar_pack_push_string(misko_success_pack,"err_code",sizeof("err_code") -1);
    yar_pack_push_long(misko_success_pack,0);

    yar_pack_push_string(misko_success_pack,"err_msg",sizeof("err_msg") -1);
    yar_pack_push_string(misko_success_pack,"success",sizeof("success") -1);

    yar_pack_push_string(misko_success_pack,"data",sizeof("data") -1);
    yar_pack_push_map(misko_success_pack,1);

    yar_pack_push_string(misko_success_pack,"count",sizeof("count") -1);
    yar_pack_push_string(misko_success_pack,log,strlen(log));
    yar_response_set_retval(response,misko_success_pack);

    yar_pack_free(misko_success_pack);

}



