package Entities

import android.os.Parcel
import android.os.Parcelable
import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "Usuarios")
class Usuarios ( nombre : String , password : String ) {

    @PrimaryKey
    @ColumnInfo(name = "nombre")
    var nombre : String

    @ColumnInfo(name = "password")
    var password : String

    init {
        this.nombre = nombre
        this.password = password
    }


    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    //    Este codigo es necesario para pasar argumentos entre fragments                     //
    //////////////////////////////////////////////////////////////////////////////////////////
    /*constructor(source: Parcel) : this(
        source.readString()!!,
        source.readString()!!
    )

    override fun describeContents() = 0

    override fun writeToParcel(dest: Parcel, flags: Int) = with(dest) {
        writeString(nombre)
        writeString(password)
    }

    companion object {
        @JvmField
        val CREATOR: Parcelable.Creator<Usuarios> = object : Parcelable.Creator<Usuarios> {
            override fun createFromParcel(source: Parcel): Usuarios = Usuarios(source)
            override fun newArray(size: Int): Array<Usuarios?> = arrayOfNulls(size)
        }
    }*/

    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
}