package Entities

import android.app.Application
import com.google.firebase.storage.StorageReference


object  GlobalVar : Application() {
    var globalVar: Int = 1  // Items count
    var globalArray : MutableList<StorageReference> = mutableListOf()
}