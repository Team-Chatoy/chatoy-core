#include <jni_Utils.h>

#include <chatoy/user.hpp>
#include <chatoy/room.hpp>


auto resp_to_object(
  JNIEnv *env,
  const chatoy::Resp& resp
) -> jobject {
  jclass respClass = env->FindClass("jni/Resp");
  jobject respObj = env->AllocObject(respClass);

  jfieldID codeField = env->GetFieldID(respClass, "code", "I");
  jfieldID msgField = env->GetFieldID(respClass, "msg", "Ljava/lang/String;");

  env->SetIntField(respObj, codeField, resp.code);
  env->SetObjectField(respObj, msgField, env->NewStringUTF(resp.msg.c_str()));

  return respObj;
}


/*
 * Class:     jni_Utils
 * Method:    register
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljni/Resp;
 */
JNIEXPORT auto JNICALL
Java_jni_Utils_register(
  JNIEnv *env,
  jobject self,
  jstring server,
  jstring username,
  jstring password
) -> jobject {
  const char *serverCstr = env->GetStringUTFChars(server, nullptr);
  const char *usernameCstr = env->GetStringUTFChars(username, nullptr);
  const char *passwordCstr = env->GetStringUTFChars(password, nullptr);

  auto res = chatoy::regist(serverCstr, usernameCstr, passwordCstr);

  return resp_to_object(env, res);
}


/*
 * Class:     jni_Utils
 * Method:    login
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljni/Resp;
 */
JNIEXPORT auto JNICALL
Java_jni_Utils_login(
  JNIEnv *env,
  jobject self,
  jstring server,
  jstring username,
  jstring password
) -> jobject {
  const char *serverCstr = env->GetStringUTFChars(server, nullptr);
  const char *usernameCstr = env->GetStringUTFChars(username, nullptr);
  const char *passwordCstr = env->GetStringUTFChars(password, nullptr);

  auto res = chatoy::login(serverCstr, usernameCstr, passwordCstr);

  return resp_to_object(env, res);
}


/*
 * Class:     jni_Utils
 * Method:    getUserInfo
 * Signature: (Ljava/lang/String;I)Ljni/User;
 */
JNIEXPORT auto JNICALL
Java_jni_Utils_getUserInfo(
  JNIEnv *env,
  jobject self,
  jstring server,
  jint id
) -> jobject {
  const char *serverCstr = env->GetStringUTFChars(server, nullptr);

  auto res = chatoy::get_user(serverCstr, id);

  jclass userClass = env->FindClass("jni/User");
  jobject user = env->AllocObject(userClass);

  jfieldID idField = env->GetFieldID(userClass, "id", "I");
  env->SetIntField(user, idField, res.id);

  jfieldID usernameField = env->GetFieldID(userClass, "username", "Ljava/lang/String;");
  env->SetObjectField(user, usernameField, env->NewStringUTF(res.username.c_str()));

  jfieldID nicknameField = env->GetFieldID(userClass, "nickname", "Ljava/lang/String;");
  env->SetObjectField(user, nicknameField, env->NewStringUTF(res.nickname.c_str()));

  jfieldID sloganField = env->GetFieldID(userClass, "slogan", "Ljava/lang/String;");
  env->SetObjectField(user, sloganField, env->NewStringUTF(res.slogan.c_str()));

  jfieldID statusField = env->GetFieldID(userClass, "status", "I");
  env->SetIntField(user, statusField, res.status);

  jfieldID registeredField = env->GetFieldID(userClass, "registered", "Ljava/lang/String;");
  env->SetObjectField(user, registeredField, env->NewStringUTF(res.registered.c_str()));

  return user;
}


/*
 * Class:     jni_Utils
 * Method:    createRoom
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT auto JNICALL
Java_jni_Utils_createRoom(
  JNIEnv *env,
  jobject self,
  jstring server,
  jstring token,
  jstring name
) -> jint {
  const char *serverCstr = env->GetStringUTFChars(server, nullptr);
  const char *tokenCstr = env->GetStringUTFChars(token, nullptr);
  const char *nameCstr = env->GetStringUTFChars(name, nullptr);

  auto res = chatoy::create_room(serverCstr, tokenCstr, nameCstr);

  return res.id;
}


/*
 * Class:     jni_Utils
 * Method:    joinRoom
 * Signature: (Ljava/lang/String;Ljava/lang/String;I)Ljni/Resp;
 */
JNIEXPORT auto JNICALL
Java_jni_Utils_joinRoom(
  JNIEnv *env,
  jobject self,
  jstring server,
  jstring token,
  jint id
) -> jobject {
  const char *serverCstr = env->GetStringUTFChars(server, nullptr);
  const char *tokenCstr = env->GetStringUTFChars(token, nullptr);

  auto res = chatoy::join_room(serverCstr, tokenCstr, id);

  return resp_to_object(env, res);
}


auto room_to_object(
  JNIEnv *env,
  const chatoy::RoomInfo& room
) -> jobject {
  jclass roomClass = env->FindClass("jni/Room");
  jobject roomObj = env->AllocObject(roomClass);

  jfieldID idField = env->GetFieldID(roomClass, "id", "I");
  env->SetIntField(roomObj, idField, room.id);

  jfieldID nameField = env->GetFieldID(roomClass, "name", "Ljava/lang/String;");
  env->SetObjectField(roomObj, nameField, env->NewStringUTF(room.name.c_str()));

  jfieldID descriptionField = env->GetFieldID(roomClass, "description", "Ljava/lang/String;");
  env->SetObjectField(roomObj, descriptionField, env->NewStringUTF(room.description.c_str()));

  jfieldID createdField = env->GetFieldID(roomClass, "created", "Ljava/lang/String;");
  env->SetObjectField(roomObj, createdField, env->NewStringUTF(room.created.c_str()));

  return roomObj;
}


/*
 * Class:     jni_Utils
 * Method:    getRoomInfo
 * Signature: (Ljava/lang/String;I)Ljni/Room;
 */
JNIEXPORT auto JNICALL
Java_jni_Utils_getRoomInfo(
  JNIEnv *env,
  jobject self,
  jstring server,
  jint id
) -> jobject {
  const char *serverCstr = env->GetStringUTFChars(server, nullptr);

  auto res = chatoy::get_room(serverCstr, id);

  return room_to_object(env, res);
}


/*
 * Class:     jni_Utils
 * Method:    getMyRooms
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/util/List;
 */
JNIEXPORT auto JNICALL
Java_jni_Utils_getMyRooms(
  JNIEnv *env,
  jobject self,
  jstring server,
  jstring token
) -> jobject {
  const char *serverCstr = env->GetStringUTFChars(server, nullptr);
  const char *tokenCstr = env->GetStringUTFChars(token, nullptr);

  auto res = chatoy::my_rooms(serverCstr, tokenCstr);

  jclass listClass = env->FindClass("java/util/ArrayList");
  jmethodID listConstructor = env->GetMethodID(listClass, "<init>", "()V");
  jobject list = env->NewObject(listClass, listConstructor);

  jmethodID listAdd = env->GetMethodID(listClass, "add", "(Ljava/lang/Object;)Z");

  for (const auto& room : res) {
    env->CallBooleanMethod(list, listAdd, room_to_object(env, room));
  }

  return list;
}
