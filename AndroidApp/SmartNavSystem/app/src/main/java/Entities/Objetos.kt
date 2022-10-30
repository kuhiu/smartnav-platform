package Entities

import android.os.Parcel
import android.os.Parcelable
import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "Objetos")
class Objetos ( nombre : String , src : String, obj_img : Int ) : Parcelable {

    @PrimaryKey
    @ColumnInfo(name = "nombre")
    var nombre : String

    @ColumnInfo(name = "src")
    var src : String

    @ColumnInfo(name = "obj_img")
    var obj_img : Int

    init {
        this.nombre = nombre
        this.src = src
        this.obj_img = obj_img
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    //    Este codigo es necesario para pasar argumentos entre fragments                     //
    //////////////////////////////////////////////////////////////////////////////////////////
    constructor(source: Parcel) : this(
        source.readString()!!,
        source.readString()!!,
        source.readInt()!!
    )

    override fun describeContents() = 0

    override fun writeToParcel(dest: Parcel, flags: Int) = with(dest) {
        writeString(nombre)
        writeString(src)
    }

    companion object {
        @JvmField
        val CREATOR: Parcelable.Creator<Objetos> = object : Parcelable.Creator<Objetos> {
            override fun createFromParcel(source: Parcel): Objetos = Objetos(source)
            override fun newArray(size: Int): Array<Objetos?> = arrayOfNulls(size)
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
}

